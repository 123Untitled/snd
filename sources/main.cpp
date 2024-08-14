#include "track.hpp"
#include "string.hpp"
#include "map.hpp"

#include <unordered_map>
#include <map>

#include "triggers.hpp"

#include "midi/coremidi/eventlist.hpp"
#include "midi/coremidi/coremidi.hpp"


namespace snd {



	template <snd::string... ___names>
	class pattern final {


		private:

			using ___map = snd::map<snd::track, ___names...>;

			using ___proto = auto (*)(___map&) -> void;

			/* tracks */
			___map _tracks;

			/* conditions */
			___proto _conditions;

			std::vector<coremidi::source> _msrcs;

			coremidi::eventlist _evs;



		public:

			/* default constructor */
			pattern(void)
			: _tracks{}, _conditions{nullptr}, _msrcs{}, _evs{} {

				_msrcs = coremidi::sources();

			}


			/* play */
			auto play(const snd::size_t& timeline) -> void {

				// loop over tracks
				_tracks.for_each([](auto& ___track, const snd::size_t& ___time) -> void {
					___track.update(___time);
				}, timeline);

				// conditions
				if (_conditions)
					_conditions(_tracks);

				// send midi
				_tracks.for_each([&](auto& ___track) -> void {
					// if trigger
					if (___track.trigger()) {
						// send note
						_evs.note_on(
								___track.channel(),
										___track.notes().modified(),
										100);
						// reset trigger
						___track.trigger(false);
					}
				});

				_evs.send(_msrcs[0]);
				_evs.clear();

			}

			/* conditions */
			auto conditions(___proto ___proto) -> void {
				_conditions = ___proto;
			}

			/* get as friend */
			template <snd::string, snd::string... ___ks>
			friend constexpr auto get(snd::pattern<___ks...>&) noexcept -> snd::track&;

	}; // class pattern


	/* get */
	template <snd::string ___key, snd::string... ___keys>
	constexpr auto get(snd::pattern<___keys...>& ___pat) noexcept -> snd::track& {
		return snd::get<___key>(___pat._tracks);
	}

}


int main(void) {

	snd::pattern<"kick", "bass", "lead", "hithat"> pat;

	pat.conditions([](auto& ___map) -> void {

		// get track
		auto& kick = snd::get<"kick">(___map);
		auto& bass = snd::get<"bass">(___map);
		auto& hithat = snd::get<"hithat">(___map);

		//return;
		if (kick.trigger() && bass.trigger()) {

			if (hithat.trigger()) {
				bass.notes().modified(103);
			}

			else {
				//bass.notes().modified(79);
			}
		}

		else {
			bass.note(bass.notes().current());
		}


	});


	{
		auto& kick = snd::get<"kick">(pat);

		kick.channel(0U).triggers().signature(1, 16).insert(
			1, 0, 0, 1, 0, 0, 0, 0,
			1, 0, 0, 1, 0, 0, 0, 0
		);
	}


	{
		auto& bass = snd::get<"bass">(pat);

		bass.channel(1U);
		bass.triggers().signature(1, 8).insert(1, 0, 1);
		bass.notes().signature(1, 1).insert(70, 60);
	}

	{
		auto& hithat = snd::get<"hithat">(pat);

		hithat.channel(2U).triggers().signature(1, 16).insert(1, 0, 1, 0, 1, 0, 1);
	}

	{
		auto& lead = snd::get<"lead">(pat);

		lead.channel(1U);
		lead.triggers().signature(1, 8).insert(1, 0, 1, 0, 1);
		lead.notes().signature(1, 1).insert(89, 88);
	}




	// compute in microseconds 130bpm at 24ppq
	const snd::size_t bpm = 130U;

	snd::size_t timeline = 0U;

	const long microsecondsPerMinute = 60 * 1000000; // 60 seconds * 1,000,000 microseconds per second
    const int pulsesPerQuarterNote = 24;
    long inter = microsecondsPerMinute / (bpm * pulsesPerQuarterNote);

	snd::size_t time = 1U;

	while (true) {
		pat.play(timeline);


		if (timeline % 24 == 0) {
			std::cout << '\r' << time << std::flush;
			time = time == 4 ? 1 : time + 1;
		}

		// sleep
		::usleep(inter);
		++timeline;

	}




	return 0;
}

#include "track.hpp"
#include "string.hpp"
#include "map.hpp"
#include "running.hpp"

#include <unordered_map>
#include <map>

#include "triggers.hpp"
#include "time/clock.hpp"

#include "midi/coremidi/eventlist.hpp"
#include "midi/coremidi/coremidi.hpp"


namespace snd {




	template <snd::string... ___names>
	class pattern final : public snd::clockable {


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

			auto clock_start(void) -> void override {
				_evs.start();
				_evs.send(_msrcs[0]);
				_evs.clear();
			}

			/* stop */
			auto clock_stop(void) -> void override {
				_evs.stop();
				_evs.send(_msrcs[0]);
				_evs.clear();
			}

			/* tick */
			auto clock_tick(const snd::size_t& timeline) -> void override {
				play(timeline);
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

	snd::pattern<"kick", "bass"> pat;

	pat.conditions([](auto& ___map) -> void {

		// get track
		auto& kick = snd::get<"kick">(___map);
		auto& bass = snd::get<"bass">(___map);


		bass.trigger(kick.trigger());

		//return;
		if (kick.trigger()) {
		}

		else {
		}


	});


	{
		auto& kick = snd::get<"kick">(pat);

		kick.channel(0U).triggers().signature(1, 16).insert(
			1,0,0,0,   1,0,0,0,   0,0,1,0,   0,0,0,0
		);
		kick.notes().signature(1, 4).insert(40, 36, 36, 36);
	}


	{
		auto& bass = snd::get<"bass">(pat);

		bass.channel(1U);
		bass.triggers().signature(1, 2).insert(0, 0, 0, 0, 0);
		bass.notes().signature(1, 1).insert(35, 38, 31, 31);
	}



	// start ------------------------------

	// record signal SIGINT
	signal(SIGINT, [](int) -> void {
		snd::running::stop();
	});

	snd::clock cl;

	cl.start(pat);

	return 0;
}

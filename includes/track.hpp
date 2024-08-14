#ifndef ___CODE_TRACK_HPP___
#define ___CODE_TRACK_HPP___

#include "signature.hpp"
#include "sequence.hpp"
#include "string.hpp"
#include "triggers.hpp"
#include "notes.hpp"

#include <vector>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- T R A C K -----------------------------------------------------------

	class track final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::track;


			// -- private constants -------------------------------------------

			enum : unsigned char {
				S_TRIGGERS = 0,
				S_NOTES,
				S_OCTAVES,
				S_VELOCITIES,
				S_GATES,
				S_NUM_SEQUENCES,
			};


			// -- private members ---------------------------------------------

			/* channel */
			snd::size_t _channel;

			/* triggers */
			snd::triggers _triggers;

			/* notes */
			snd::notes _notes;



		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			track(void) noexcept = default;

			// -- public methods ----------------------------------------------

			/* update */
			auto update(const snd::size_t& timeline) -> void {
				_triggers.update(timeline);
				   _notes.update(timeline);
			}




			// -- public accessors --------------------------------------------

			/* channel */
			auto channel(void) const noexcept -> const snd::size_t& {
				return _channel;
			}

			/* triggers */
			auto triggers(void) noexcept -> snd::triggers& {
				return _triggers;
			}

			/* notes */
			auto notes(void) noexcept -> snd::notes& {
				return _notes;
			}

			/* trigger */
			auto trigger(void) const noexcept -> auto {
				return _triggers.modified();
			}

			/* note */
			auto note(void) const noexcept -> auto {
				return _notes.modified();
			}

			/* octave */
			auto octave(void) const noexcept -> snd::size_t {
				return 0;
			}

			/* velocity */
			auto velocity(void) const noexcept -> snd::size_t {
				return 0;
			}

			/* gate */
			auto gate(void) const noexcept -> snd::size_t {
				return 0;
			}


			// -- public modifiers --------------------------------------------

			/* channel */
			auto channel(const snd::size_t& channel) noexcept -> ___self& {
				_channel = channel;
				return *this;
			}

			/* trigger */
			auto trigger(const bool& ___tr) noexcept -> void {
				_triggers.modified(___tr);
			}

			/* note */
			auto note(const snd::u8& ___nt) noexcept -> void {
				_notes.modified(___nt);
			}

			/* octave */
			auto octave(const snd::size_t& octave) noexcept -> void {
			}

			/* velocity */
			auto velocity(const snd::size_t& velocity) noexcept -> void {
			}

			/* gate */
			auto gate(const snd::size_t& gate) noexcept -> void {
			}






	}; // class track

} // namespace snd

#endif // ___CODE_TRACK_HPP___

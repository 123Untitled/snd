#ifndef ___SND_NOTES_HPP___
#define ___SND_NOTES_HPP___

#include "sequence.hpp"
#include "types.hpp"


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- T R I G G E R S -----------------------------------------------------

	class notes final : public snd::sequence<snd::u8> {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::notes;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			notes(void)
			: snd::sequence<snd::u8>(60U) {
			}

			/* copy constructor */
			notes(const ___self&) = default;

			/* move constructor */
			notes(___self&&) noexcept = default;

			/* destructor */
			~notes(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


		private:

			// -- private overrides -------------------------------------------

			/* clamp */
			auto _clamp(const snd::u8& ___vl) const noexcept -> snd::u8 override {
				// clamp to MIDI note range
				return (___vl > 0x7FU) ? 0x7FU : ___vl;
			}

	}; // class notes

} // namespace snd

#endif // ___SND_NOTES_HPP___

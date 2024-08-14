#ifndef ___MSH_TIME_BPM_HPP___
#define ___MSH_TIME_BPM_HPP___

#include "types.hpp"


// -- M S H  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- B P M ---------------------------------------------------------------

	class bpm final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::bpm;


			// -- private members ---------------------------------------------

			/* beats per minute */
			snd::size_t _bpm;


			// -- private constants -------------------------------------------

			/* constant */
			enum : snd::size_t {
				NANO_PER_MIN = 60'000'000'000U
			};


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			bpm(void) noexcept
			: _bpm{120U} {
			}

			/* bpm constructor */
			bpm(const snd::size_t bpm) noexcept
			: _bpm{bpm} {
			}

			/* copy constructor */
			bpm(const ___self&) noexcept = default;

			/* move constructor */
			bpm(___self&&) noexcept = default;

			/* destructor */
			~bpm(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;

			/* bpm assignment operator */
			auto operator=(const snd::size_t bpm) noexcept -> ___self& {
				_bpm = bpm;
				return *this;
			}


			// -- public conversion operators ---------------------------------

			/* msh::u32 conversion operator */
			explicit operator snd::size_t(void) const noexcept {
				return _bpm;
			}

#define MIDI_PPQN 24U

			// -- public methods ----------------------------------------------

			/* to nanoseconds */
			auto to_nano(void) const noexcept -> snd::size_t {
				return NANO_PER_MIN / (_bpm * MIDI_PPQN);
			}

	}; // class bpm

} // namespace msh

#endif // ___MSH_TIME_BPM_HPP___

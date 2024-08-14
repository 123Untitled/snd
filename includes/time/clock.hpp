#ifndef ___SND_TIME_CLOCK_HPP___
#define ___SND_TIME_CLOCK_HPP___

#include "types.hpp"
#include "time/timebase.hpp"
#include "bpm.hpp"

#include <ctime>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- C L O C K A B L E ---------------------------------------------------

	class clockable {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::clockable;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			clockable(void) noexcept = default;

			/* copy constructor */
			clockable(const ___self&) noexcept = default;

			/* move constructor */
			clockable(___self&&) noexcept = default;

			/* destructor */
			virtual ~clockable(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public interface --------------------------------------------

			/* start */
			virtual auto clock_start(void) -> void = 0;

			/* stop */
			virtual auto clock_stop(void) -> void = 0;

			/* tick */
			virtual auto clock_tick(const snd::size_t&) -> void = 0;

	}; // class clockable


	// -- C L O C K -----------------------------------------------------------

	class clock final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::clock;


			// -- private members ---------------------------------------------

			/* timebase */
			msh::timebase _timebase;

			/* bpm */
			snd::bpm _bpm;

			/* nano clock */
			msh::i64 _nano_clock;

			/* nano target */
			msh::i64 _nano_target;

			/* count */
			msh::u64 _count;


			/* timeline */
			double _timeline;

			/* request */
			struct ::timespec  _request;

			msh::i64 _start;
			msh::i64 _last_start;
			msh::i64 _end;

			msh::i64 _elapsed;
			msh::i64 _acc_ref;
			msh::i64 _acc_stamp;
			msh::i64 _acc_diff;
			msh::i64 _loop_diff;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			clock(void) noexcept;

			/* deleted copy constructor */
			clock(const ___self&) = delete;

			/* deleted move constructor */
			clock(___self&&) = delete;

			/* destructor */
			~clock(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- public methods ----------------------------------------------

			/* start */
			auto start(msh::clockable&) -> void;

			/* stop */
			auto stop(void) noexcept -> void;


			// -- public modifiers --------------------------------------------

			/* bpm */
			auto bpm(const msh::u8) noexcept -> void;


			// -- public accessors --------------------------------------------

			/* bpm */
			auto bpm(void) const noexcept -> const msh::bpm&;

			/* count */
			auto count(void) const noexcept -> msh::u64;

			/* timeline */
			auto timeline(void) const noexcept -> double;


		private:

			// -- private methods ---------------------------------------------

			/* init clock */
			auto _init_clock(void) noexcept -> void;

			/* begin */
			auto _begin(void) noexcept -> void;

			/* compute timeline */
			auto _compute_timeline(void) noexcept -> void;

			/* compute diff */
			auto _compute_diff(void) noexcept -> void;

			/* sleep */
			auto _sleep(void) noexcept -> void;

			/* now */
			auto _now(void) const noexcept -> msh::u64;

	}; // class clock

} // namespace msh

#endif // ___MSH_TIME_CLOCK_HPP___

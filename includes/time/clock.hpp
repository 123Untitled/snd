#ifndef ___SND_TIME_CLOCK_HPP___
#define ___SND_TIME_CLOCK_HPP___

#include "types.hpp"
#include "time/timebase.hpp"
#include "bpm.hpp"

#include <ctime>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {

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

	// -- C L O C K A B L E ---------------------------------------------------

	class player : public snd::clockable {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::player;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			player(void) noexcept = default;

			/* copy constructor */
			player(const ___self&) noexcept = default;

			/* move constructor */
			player(___self&&) noexcept = default;

			/* destructor */
			virtual ~player(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public interface --------------------------------------------

			/* start */
			auto clock_start(void) -> void override {
				// do nothing
			}

			/* stop */
			auto clock_stop(void) -> void override {
				// do nothing
			}

			/* tick */
			auto clock_tick(const snd::size_t&) -> void override {
				// do nothing
			}

	}; // class player


	// -- C L O C K -----------------------------------------------------------

	class clock final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::clock;


			// -- private members ---------------------------------------------

			/* timebase */
			snd::timebase _timebase;

			/* bpm */
			snd::bpm _bpm;

			/* nano clock */
			snd::i64 _nano_clock;

			/* nano target */
			snd::i64 _nano_target;

			/* count */
			snd::u64 _count;


			/* timeline */
			double _timeline;

			/* request */
			struct ::timespec  _request;

			snd::i64 _start;
			snd::i64 _last_start;
			snd::i64 _end;
			snd::i64 _elapsed;
			snd::i64 _acc_ref;
			snd::i64 _acc_stamp;
			snd::i64 _acc_diff;
			snd::i64 _loop_diff;


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
			auto start(snd::clockable&) -> void;

			/* stop */
			auto stop(void) noexcept -> void;


			// -- public modifiers --------------------------------------------

			/* bpm */
			auto bpm(const snd::u8) noexcept -> void;


			// -- public accessors --------------------------------------------

			/* bpm */
			auto bpm(void) const noexcept -> const snd::bpm&;

			/* count */
			auto count(void) const noexcept -> snd::u64;

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
			auto _now(void) const noexcept -> snd::u64;

	}; // class clock

} // namespace snd

#endif // ___MSH_TIME_CLOCK_HPP___

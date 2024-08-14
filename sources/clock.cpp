#include "time/clock.hpp"
#include "time/realtime.hpp"
#include "running.hpp"

#include "config/os.hpp"

#if defined(MSH_APPLE)
#include <mach/mach_time.h>

//#include <mach/mach_time.h>

//#define NANO_PER_MIN	60'000'000'000
#define MS_PER_MIN		60'000
#define NANO_PER_SEC	 1'000'000'000
#define NANO_PER_MS		 1'000'000



// -- C L O C K ---------------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* default constructor */
snd::clock::clock(void) noexcept
: _timebase{} {
}







// -- public methods ----------------------------------------------------------

/* run */
auto snd::clock::start(snd::clockable& obj) -> void {

	snd::running::start();

	// set realtime thread
	if (snd::realtime(_nano_clock, _timebase))
		return;

	___self::bpm(160);

	___self::_init_clock();


	// start notification
	obj.clock_start();

	// loop while running
	while (snd::running::state()) {


		___self::_begin();
		___self::_compute_timeline();


		// tick notification
		obj.clock_tick(_count);

		___self::_compute_diff();
		___self::_sleep();

		++_count;
	}

	// stop notification
	obj.clock_stop();
}


// -- public modifiers --------------------------------------------------------

/* bpm */
auto snd::clock::bpm(const snd::u8 bpm) noexcept -> void {
	_bpm         = bpm;
	_nano_clock  = _bpm.to_nano();
	_nano_target = _nano_clock;
}


// -- public accessors --------------------------------------------------------

/* bpm */
auto snd::clock::bpm(void) const noexcept -> const snd::bpm& {
	return _bpm;
}

/* count */
auto snd::clock::count(void) const noexcept -> snd::u64 {
	return _timeline;
}



// -- private methods ---------------------------------------------------------

/* init clock */
auto snd::clock::_init_clock(void) noexcept -> void {

	_count		= 0;

	_start		= 0;
	_last_start = ___self::_now();
	_end		= _last_start + _nano_clock;

	_elapsed	= 0;
	_acc_ref	= 0;
	_acc_stamp	= 0;
	_acc_diff	= 0;
	_loop_diff	= 0;
	_timeline	= 0;

	// secondes number
	_request.tv_sec = 0;
	// nanosecondes number
	_request.tv_nsec = static_cast<long>(_nano_clock - (_nano_clock / 100));
}

/* begin */
auto snd::clock::_begin(void) noexcept -> void {
	_start = ___self::_now();
}

/* compute timeline */
auto snd::clock::_compute_timeline(void) noexcept -> void {

	// accumulate elapsed time
	_timeline += static_cast<double>(_elapsed)
			   / static_cast<double>(NANO_PER_SEC);
}

/* compute diff */
auto snd::clock::_compute_diff(void) noexcept -> void {

	_elapsed = _end - _last_start;

	//loop_diff = _elapsed - nanoClock;


	_acc_stamp += _elapsed;
	_acc_ref   += _nano_clock;

	if (_acc_stamp > _acc_ref) {

		_acc_diff   = _acc_stamp - _acc_ref;
		_nano_target = _nano_clock - _acc_diff;
	}

	else if (_acc_stamp < _acc_ref) {

		_acc_diff   = _acc_ref   - _acc_stamp;
		_nano_target = _nano_clock + _acc_diff;
	}

	// else if (_acc_ref == _acc_stamp)
	else {

		/*temp code*/ _acc_diff = 0;
		_nano_target = _nano_clock;
		_acc_stamp	= 0;
		_acc_ref	= 0;
	}
	//std::cout << "now: " << now() << std::endl;
	//std::cout << "timestamp: " << mach_absolute_time() << std::endl;

	//std::cout << _acc_diff << std::endl;

	_request.tv_nsec = static_cast<long>(_nano_target
					- (_nano_target / 100));

	_last_start = _start;
}

/* sleep */
auto snd::clock::_sleep(void) noexcept -> void {

	// delay sleep
	::nanosleep(&_request, nullptr);
	_end = ___self::_now();

	// busy wait
	while ((_end - _start) < _nano_target)
		_end = ___self::_now();
}

/* now */
auto snd::clock::_now(void) const noexcept -> snd::u64 {
	return ::mach_absolute_time() * _timebase.absolute_to_nano();
	// ::mach_continuous_time()
}

#endif // MSH_APPLE

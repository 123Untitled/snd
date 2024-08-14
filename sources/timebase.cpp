#include "time/timebase.hpp"

#include "config/os.hpp"

#if defined(MSH_APPLE)
#include <mach/mach_time.h>


// -- T I M E B A S E ---------------------------------------------------------

// -- public lifecycle --------------------------------------------------------

/* default constructor */
snd::timebase::timebase(void) {

	// timebase info
	::mach_timebase_info_data_t timebase;

	// get timebase info
	if (::mach_timebase_info(&timebase) != KERN_SUCCESS) {
		// error
		return;
	}

	// nano per millisecond
	constexpr unsigned nano_per_ms = 1'000'000;

	// absolute clock to nanoseconds
	_absolute_to_nano = static_cast<double>(timebase.numer)
					  / static_cast<double>(timebase.denom);

	// milliseconds to absolute clock
	_ms_to_absolute = (static_cast<double>(timebase.denom)
					 / static_cast<double>(timebase.numer)) * nano_per_ms;

	// nanoseconds to absolute clock
	_nano_to_absolute = static_cast<double>(timebase.denom)
					  / static_cast<double>(timebase.numer);
}


// -- public accessors --------------------------------------------------------

/* ms to absolute */
auto snd::timebase::ms_to_absolute(void) const noexcept -> double {
	return _ms_to_absolute;
}

/* absolute to nano */
auto snd::timebase::absolute_to_nano(void) const noexcept -> double {
	return _absolute_to_nano;
}

/* nano to absolute */
auto snd::timebase::nano_to_absolute(void) const noexcept -> double {
	return _nano_to_absolute;
}

#endif

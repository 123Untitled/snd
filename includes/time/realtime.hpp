#ifndef ___MSH_TIME_REALTIME_HPP___
#define ___MSH_TIME_REALTIME_HPP___

#include "types.hpp"


// -- M S H  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- forward declarations ------------------------------------------------

	/* timebase */
	class timebase;


	// -- R E A L T I M E -----------------------------------------------------

	/* realtime */
	auto realtime(const snd::i64&, const snd::timebase&) noexcept -> bool;

} // namespace msh

#endif // ___MSH_TIME_REALTIME_HPP___

#ifndef ___MSH_TIME_REALTIME_HPP___
#define ___MSH_TIME_REALTIME_HPP___

#include "msh/types.hpp"


// -- M S H  N A M E S P A C E ------------------------------------------------

namespace msh {


	// -- forward declarations ------------------------------------------------

	/* timebase */
	class timebase;


	// -- R E A L T I M E -----------------------------------------------------

	/* realtime */
	auto realtime(const msh::i64&, const msh::timebase&) noexcept -> bool;

} // namespace msh

#endif // ___MSH_TIME_REALTIME_HPP___

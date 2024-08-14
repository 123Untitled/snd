#ifndef ___MSH_COREMIDI_HPP___
#define ___MSH_COREMIDI_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include <vector>
#include "midi/coremidi/source.hpp"
#include "midi/coremidi/destination.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	/* sources */
	auto sources(void) -> std::vector<coremidi::source>;

	/* destinations */
	auto destinations(void) -> std::vector<coremidi::destination>;

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_HPP___

#include "midi/coremidi/coremidi.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/types.hpp"

/* sources */
auto coremidi::sources(void) -> std::vector<coremidi::source> {

	// get number of sources
	const coremidi::item_count num_sources = ::MIDIGetNumberOfSources();

	// create sources
	std::vector<coremidi::source> sources;
	sources.reserve(num_sources);

	// iterate over sources
	for (coremidi::item_count i = 0U; i < num_sources; ++i) {

		// get source
		const coremidi::endpoint_reference source = ::MIDIGetSource(i);

		// create source
		sources.emplace_back(source);
	}

	// return sources
	return sources;
}

/* destinations */
auto coremidi::destinations(void) -> std::vector<coremidi::destination> {

	// get number of destinations
	const coremidi::item_count num_destinations = ::MIDIGetNumberOfDestinations();

	// create destinations
	std::vector<coremidi::destination> destinations;
	destinations.reserve(num_destinations);

	// iterate over destinations
	for (coremidi::item_count i = 0U; i < num_destinations; ++i) {

		// get destination
		const coremidi::endpoint_reference destination = ::MIDIGetDestination(i);

		// create destination
		destinations.emplace_back(destination);
	}

	// return destinations
	return destinations;
}

#endif // MSH_APPLE

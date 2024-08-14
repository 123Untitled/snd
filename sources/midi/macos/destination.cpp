#include "midi/coremidi/destination.hpp"

#if defined(MSH_APPLE)

#include "midi/corefoundation/string.hpp"


// -- D E S T I N A T I O N ---------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* id constructor */
coremidi::destination::destination(const ::MIDIEndpointRef& ref)
: coremidi::object{ref},
  _external{true} {
}

/* name constructor */
coremidi::destination::destination(const coremidi::client& client, const char* name)
: _external{false} {

	// create cfstring
	corefoundation::string cstr{name};

	// create a new destination
	const ::OSStatus err = ::MIDIDestinationCreateWithProtocol(client.id(),
															   cstr,
															   kMIDIProtocol_1_0,
															   &_ref,
															   ^(const ::MIDIEventList* evtlist, void*) {
																	coremidi::destination::_read_midi(*evtlist);
															   });

	// check if there was an error
	if (err != noErr)
		throw coremidi::exception{err, "MIDIDestinationCreateWithProtocol"};
}

/* move constructor */
coremidi::destination::destination(___self&& other) noexcept
: coremidi::object{other._ref},
  _external{other._external} {
	other._ref = 0U;
	other._external = true;
}

/* destructor */
coremidi::destination::~destination(void) noexcept {
	// dispose endpoint
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::destination::operator=(___self&& other) noexcept -> ___self& {

	// check self assignment
	if (this == &other)
		return *this;

	// dispose endpoint
	___self::_dispose();

	// move source
	_ref       = other._ref;
	other._ref = 0U;
	_external  = other._external;
	other._external = true;

	// return self
	return *this;
}

// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::destination::_dispose(void) noexcept -> void {

	// check source mode
	if (_external)
		return;

	// check endpoint validity
	if (_ref == 0U)
		return;

	// dispose endpoint
	static_cast<void>(
			::MIDIEndpointDispose(_ref)
		);
}


// -- private static methods --------------------------------------------------

/* read midi */
auto coremidi::destination::_read_midi(const ::MIDIEventList& evtlist) -> void {
	//static_cast<void>(evtlist);
	//if (evtlist == nullptr) { return; }

	std::cout << "numPackets: " << evtlist.numPackets << std::endl;

	for (std::size_t i = 0; i < evtlist.numPackets; ++i) {

		const MIDIEventPacket& packet = evtlist.packet[i];

		std::cout << "wordCount: " << packet.wordCount << std::endl;

		for (std::size_t j = 0; j < packet.wordCount; ++j) {

			const UInt32 word = packet.words[j];

			const UInt8 status = word & 0xFF;
			const UInt8 data1 = (word >> 8) & 0xFF;
			const UInt8 data2 = (word >> 16) & 0xFF;

			std::cout << "status: " << static_cast<int>(status) << std::endl;

			std::cout << "data1: " << static_cast<int>(data1) << std::endl;

			std::cout << "data2: " << static_cast<int>(data2) << std::endl;

		}
	}

}

#endif // MSH_COREMIDI

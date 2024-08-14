#include "midi/coremidi/client.hpp"

#if defined(MSH_APPLE)

#include "midi/corefoundation/string.hpp"

#include <unistd.h>


// -- public lifecycle --------------------------------------------------------

/* name constructor */
coremidi::client::client(const char* name) {

	// create cfstring
	corefoundation::string cstr{name};

	// create client
	::OSStatus status = ::MIDIClientCreate(cstr, _notification, this, &_ref);

	// check if there was an error
	if (status != noErr)
		throw coremidi::exception{status, "MIDIClientCreate"};
}

/* move constructor */
coremidi::client::client(___self&& other) noexcept
: coremidi::object{other._ref} {
	other._ref = 0U;
}

/* destructor */
coremidi::client::~client(void) noexcept {
	// dispose client
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::client::operator=(___self&& other) noexcept -> ___self& {

	// check for self assignment
	if (this == &other)
		return *this;

	// dispose client
	___self::_dispose();

	// move reference
	_ref       = other._ref;
	other._ref = 0U;

	return *this;
}


// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::client::_dispose(void) noexcept -> void {

	// check client validity
	if (_ref == 0U)
		return;

	return; // no need to dispose client

	// dispose client
	static_cast<void>(
			::MIDIClientDispose(_ref)
		);
}


// -- private static methods --------------------------------------------------

/* notification */
auto coremidi::client::_notification(const MIDINotification *message, void* data) noexcept -> void {

	// get client reference
	___self& client = *static_cast<___self*>(data);

	switch (message->messageID) {

		// Some aspect of the current MIDI setup changed.
		case kMIDIMsgSetupChanged:
			::write(STDIN_FILENO, "setup changed", 13);
			break;

		// The system added a device, entity, or endpoint.
		case kMIDIMsgObjectAdded:
			::write(STDIN_FILENO, "object added", 12);
			break;

		// The system removed a device, entity, or endpoint.
		case kMIDIMsgObjectRemoved:
			::write(STDIN_FILENO, "object removed", 14);
			break;

		// An object’s property value changed.
		case kMIDIMsgPropertyChanged:
			::write(STDIN_FILENO, "property changed", 16);
			break;

		// The system created or disposed of a persistent MIDI Thru connection.
		case kMIDIMsgThruConnectionsChanged:
			::write(STDIN_FILENO, "thru connection changed", 23);
			break;

		// The system changed a serial port owner.
		case kMIDIMsgSerialPortOwnerChanged:
			::write(STDIN_FILENO, "serial port owner changed", 25);
			break;

		// An I/O error occurred.
		case kMIDIMsgIOError:
			::write(STDIN_FILENO, "io error", 8);
			break;

		default:
			::write(STDIN_FILENO, "unknown notification", 20);
	}
}

#endif // MSH_APPLE

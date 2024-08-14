#include "midi/coremidi/source.hpp"

#if defined(MSH_APPLE)

#include "midi/corefoundation/string.hpp"


// -- S O U R C E -------------------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* id constructor */
coremidi::source::source(const ::MIDIEndpointRef& ref)
: coremidi::object{ref},
  _external{true} {
}

/* name constructor */
coremidi::source::source(const coremidi::client& client, const char* name)
: _external{false} {

	// create cfstring
	corefoundation::string cstr{name};

	// create a new source
	const ::OSStatus err = ::MIDISourceCreateWithProtocol(client.id(),
														  cstr,
														  kMIDIProtocol_1_0,
														  &_ref);

	// check if there was an error
	if (err != noErr)
		throw coremidi::exception{err, "MIDISourceCreateWithProtocol"};
}

/* move constructor */
coremidi::source::source(___self&& other) noexcept
: coremidi::object{other._ref},
  _external{other._external} {
	other._ref = 0U;
	other._external = true;
}

/* destructor */
coremidi::source::~source(void) noexcept {
	// dispose source
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::source::operator=(___self&& other) noexcept -> ___self& {

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
auto coremidi::source::_dispose(void) noexcept -> void {

	// check source mode
	if (_external)
		return;

	// check source validity
	if (_ref == 0U)
		return;

	// dispose endpoint
	static_cast<void>(
		::MIDIEndpointDispose(_ref)
		);
}

#endif // MSH_APPLE

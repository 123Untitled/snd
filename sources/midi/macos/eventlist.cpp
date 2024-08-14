#include "midi/coremidi/eventlist.hpp"

#if defined(MSH_APPLE)

/* default constructor */
coremidi::eventlist::eventlist(void)
: _buffer{}, _list{nullptr}, _packet{nullptr} {

	// reserve default buffer size
	_buffer.resize(BUFFER_SIZE);

	// initialize the event list
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());

	// initialize the event packet
	_packet = ::MIDIEventListInit(_list, kMIDIProtocol_1_0);
}

/* copy constructor */
coremidi::eventlist::eventlist(const ___self& other)
: _buffer{other._buffer},
  _list{reinterpret_cast<MIDIEventList*>(_buffer.data())},
  _packet{&(_list->packet[_list->numPackets ? (_list->numPackets - 1U) : 0U])} {
}


// -- public modifiers --------------------------------------------------------

/* clear */
auto coremidi::eventlist::clear(void) -> void {

	// initialize the event packet
	_packet = ::MIDIEventListInit(_list, kMIDIProtocol_1_0);

	if (_packet == nullptr)
		throw coremidi::exception{0, "failed to clear event list"};
}

/* send */
auto coremidi::eventlist::send(const coremidi::source& source) -> void {

	// check packet validity
	//if (_packet == nullptr)
	//	return;

	// send midi to source device
	const ::OSStatus err = ::MIDIReceivedEventList(source.id(), _list);

	if (err != noErr)
		throw coremidi::exception{err, "failed to send event list"};
}



/* note on */
auto coremidi::eventlist::note_on(const coremidi::u8 channel,
								  const coremidi::u8 note,
								  const coremidi::u8 velocity) -> void {

	___self::_add(::MIDI1UPNoteOn(0U, channel, note, velocity));
}

/* note off */
auto coremidi::eventlist::note_off(const coremidi::u8 channel,
								   const coremidi::u8 note) -> void {

	___self::_add(::MIDI1UPNoteOff(0U, channel, note, 0U));
}

//UInt32 msg = MIDICLOCKTICK;
/*
msg = on ? 0x20900000 : 0x20800000; // note on or off
msg = msg | ((note & 0x7F) << 8); // note
msg = msg | 127; // velocity
*/



/* common midi messages */
enum : coremidi::m32 {
	CLOCK = 0x10F80000,
	START = 0x10FA0000, STOP  = 0x10FC0000,
	ON    = 0x20900000, OFF   = 0x20800000
};


/* tick */
auto coremidi::eventlist::tick(void) -> void {
	___self::_add(CLOCK);
}

/* start */
auto coremidi::eventlist::start(void) -> void {
	___self::_add(START);
}

/* stop */
auto coremidi::eventlist::stop(void) -> void {
	___self::_add(STOP);
}


// -- private methods ---------------------------------------------------------

/* add */
auto coremidi::eventlist::_add(const coremidi::m32& msg) -> void {

	// check packet validity
	if (_packet == nullptr)
		return;

	addmsg:

	// add the midi message to the packet
	_packet = ::MIDIEventListAdd(_list,
								 _buffer.size(),
								 _packet,
								 0U,
								 1U,
								 &msg);

	// check packet validity
	if (!_packet) {
		std::cout << "resize buffer" << std::endl;
		// check if the buffer can be resized
		if (_resize() == false) {
			std::cout << "\x1b[32m" << "buffer full" << "\x1b[0m" << std::endl;
			exit(1);
			return;
		}
		// try again
		goto addmsg;
	}
}

/* resize */
auto coremidi::eventlist::_resize(void) -> bool {

	if (_buffer.size() == MAX_EVENT)
		return false;

	auto size = _buffer.size() * 2U;

	// check if the max number of events has been reached
	if (size > MAX_EVENT)
		size = MAX_EVENT;

	// else resize the buffer
	_buffer.resize(size);

	// update the list and packet pointers
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());

	// update the packet pointer
	const unsigned i = _list->numPackets ? (_list->numPackets - 1U) : 0U;

	_packet = &(_list->packet[i]);

	return true;
}

#endif // MSH_APPLE

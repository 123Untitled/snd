#ifndef ___MSH_COREMIDI_EVENTLIST_HPP___
#define ___MSH_COREMIDI_EVENTLIST_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/source.hpp"
#include "midi/coremidi/types.hpp"
#include "midi/coremidi/output.hpp"

#include <vector>


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- E V E N T L I S T ---------------------------------------------------

	class eventlist final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::eventlist;


			// -- private constants -------------------------------------------

			/* buffer size */
			enum : unsigned {
				BUFFER_SIZE = sizeof(::MIDIEventList),
				// The maximum size of an event list is 65,536 bytes.
				MAX_EVENT = 65'536
			};


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			eventlist(void);

			/* copy constructor */
			eventlist(const ___self&);

			/* move constructor */
			eventlist(___self&&) noexcept = default;

			/* destructor */
			~eventlist(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- public modifiers --------------------------------------------

			/* clear */
			auto clear(void) -> void;

			/* send */
			auto send(const coremidi::source&) -> void;

			/* note on */
			auto note_on(const coremidi::u8,
						 const coremidi::u8,
						 const coremidi::u8 = 100U) -> void;

			/* note off */
			auto note_off(const coremidi::u8,
						  const coremidi::u8) -> void;

			/* tick */
			auto tick(void) -> void;

			/* start */
			auto start(void) -> void;

			/* stop */
			auto stop(void) -> void;


		private:

			// -- private methods ---------------------------------------------

			/* add */
			auto _add(const coremidi::m32&) -> void;


			/* resize */
			auto _resize(void) -> bool;


			// -- private members ---------------------------------------------

			/* buffer */
			std::vector<UInt8> _buffer;

			/* A variable-length list of MIDI event packets. */
			/*       - protocol (MIDIProtocolID) -> The MIDI protocol variant of the events in the list. */
			/*       - numpackets (UInt32) -> The number of MIDI event packet structures in the list. */
			/*       - packet (MIDIEventpacket) -> An array of variable-length MIDI event packet structures. */
			::MIDIEventList* _list;

			/* A series of simultaneous MIDI events in Universal MIDI packets (UMP) format. */
			/*       - timeStamp (UInt64) -> The event packet timestamp. */
			/*       - wordCount (UInt32) -> The number of valid MIDI 32-bit words in this event packet. */
			/*       - words (UInt32 []) -> A variable-length stream of native-endian 32-bit Universal MIDI packets (UMP). */
			::MIDIEventPacket* _packet;

	}; // class eventlist

}; // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_EVENTLIST_HPP___

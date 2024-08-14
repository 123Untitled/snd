#ifndef ___COREMIDI_PLUS_PLUS_EVENT_LIST_HPP___
#define ___COREMIDI_PLUS_PLUS_EVENT_LIST_HPP___

#include "msh/config/os.hpp"

#if defined(MSH_APPLE)

#include "coremidi++/types.hpp"
#include "coremidi++/event/packet.hpp"
#include "coremidi++/endpoint.hpp"
//#include "coremidi++/port.hpp"
#include "coremidi++/output_port.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- E V E N T  N A M E S P A C E ----------------------------------------

	namespace event {


		// -- L I S T ---------------------------------------------------------

		template <coremidi::protocol_id ___id>
		class list final {


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = coremidi::event::list<___id>;


			public: // temporary

				// -- private members -----------------------------------------

				/* protocol */
				//coremidi::protocol_id _protocol;

				/* packets */
				coremidi::event::packet* _packets;

				/* capacity */
				coremidi::u32 _capacity;

				/* size */
				coremidi::u32 _size;



			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				list(void)
				: _protocol{kMIDIProtocol_1_0},
				  _size{0U},
				  _packets{nullptr} {
				}

				/* deleted copy constructor */
				list(const ___self&) = delete;

				/* move constructor */
				list(___self&& other)
				: _protocol{other._protocol},
				  _size{other._size},
				  _packets{other._packets} {
					other._size = 0U;
					other._packets = nullptr;
				}

				/* destructor */
				~list(void) noexcept {
				}


				// -- public accessors ----------------------------------------

				/* protocol */
				auto protocol(void) const noexcept -> coremidi::protocol_id {
					return _protocol;
				}

				/* size */
				auto size(void) const noexcept -> coremidi::u32 {
					return _size;
				}


				// -- public modifiers ----------------------------------------

				/* push */
				auto push(const coremidi::event::packet& packet) -> void {

					// resize the packet list
					_packets = static_cast<coremidi::event::packet*>(std::realloc(_packets, (_size + 1U) * sizeof(coremidi::event::packet)));

					// check if the packet list was resized
					if (_packets == nullptr)
						return;

					// copy the packet
					_packets[_size] = packet;

					// increment the size
					++_size;
				}


		}; // class list

	} // namespace event


	// -- non-member functions ------------------------------------------------

	inline auto send(const coremidi::endpoint& src,
					 const coremidi::event::list& evtlist) -> void {

		::MIDIEventList list;

		list.protocol = evtlist.protocol();
		list.numPackets = evtlist.size();
		list.packet = evtlist._packets;


		const ::MIDIEventList* list = reinterpret_cast<const ::MIDIEventList*>(&evtlist);

		// send midi to source device
		const ::OSStatus err = ::MIDIReceivedEventList(src.id(), list);

		// handle error
		if (err != noErr)
			;
	}

	inline auto send(const coremidi::port::output& port,
					 const coremidi::endpoint& dest,
					 const coremidi::event::list& evtlist) -> void {

		const ::MIDIEventList* list = reinterpret_cast<const ::MIDIEventList*>(&evtlist);

		// send midi to source device
		const ::OSStatus err = ::MIDISendEventList(0, dest.id(), list);
	}




} // namespace coremidi

#endif // MSH_APPLE

#endif // ___COREMIDI_PLUS_PLUS_EVENT_LIST_HPP___

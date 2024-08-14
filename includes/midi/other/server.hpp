#ifndef ___MSH_MIDI_SERVER_HPP___
#define ___MSH_MIDI_SERVER_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/client.hpp"
#include "midi/coremidi/source.hpp"
#include "midi/coremidi/eventlist.hpp"
#include "midi/coremidi/output.hpp"

#include <CoreMIDI/CoreMIDI.h>
#include <cstdint>

#include <iostream>



// -- M S H  N A M E S P A C E ------------------------------------------------

namespace msh {


	//// -- M I D I  N A M E S P A C E ------------------------------------------
	//
	//namespace midi {
	//
	//
	//	// -- S E R V E R -----------------------------------------------------
	//
	//	class server final {
	//
	//
	//		private:
	//
	//			// -- private types -------------------------------------------
	//
	//			/* self type */
	//			using ___self = msh::midi::server;
	//
	//			/* timestamp type */
	//			using timestamp = ::MIDITimeStamp;
	//
	//
	//		public:
	//
	//			// -- public lifecycle ----------------------------------------
	//
	//			/* deleted copy constructor */
	//			server(const ___self&) = delete;
	//
	//			/* deleted move constructor */
	//			server(___self&&) = delete;
	//
	//			/* destructor */
	//			~server(void) noexcept = default;
	//
	//
	//			// -- public assignment operators -----------------------------
	//
	//			/* deleted copy assignment operator */
	//			auto operator=(const ___self&) -> ___self& = delete;
	//
	//			/* deleted move assignment operator */
	//			auto operator=(___self&&) -> ___self& = delete;
	//
	//
	//			// -- public static methods -----------------------------------
	//
	//			/* note on */
	//			static auto note_on(const coremidi::u8,
	//								const coremidi::u8,
	//								const coremidi::u8 = 100U) -> void;
	//
	//			/* note off */
	//			static auto note_off(const coremidi::u8,
	//								 const coremidi::u8) -> void;
	//
	//			/* send */
	//			static auto send(void) -> void;
	//
	//
	//			static auto start(void) -> void {
	//
	//				___self::shared();
	//				//return;
	//				std::cout << "press enter to disconnect" << std::endl;
	//				//CFRunLoopRun();
	//				while (true) {
	//
	//					note_on(0, 60, 100);
	//					send();
	//					sleep(1);
	//					note_off(0, 60);
	//					send();
	//					sleep(1);
	//
	//
	//					//int c = std::getchar();
	//					//if (c == 'q') { break; }
	//				}
	//			}
	//
	//			static auto overall_info(void) -> void;
	//			static auto source_info(void) -> void;
	//
	//		private:
	//
	//			// -- private lifecycle ---------------------------------------
	//
	//			/* default constructor */
	//			server(void);
	//
	//
	//			// -- private static methods ----------------------------------
	//
	//			/* shared */
	//			static auto shared(void) -> ___self&;
	//
	//
	//			// -- private methods ---------------------------------------------
	//
	//			/* setup midi */
	//			auto setup_server(void) -> void;
	//
	//
	//			// -- private members ---------------------------------------------
	//
	//			/* client */
	//			coremidi::client _client;
	//
	//			/* source */
	//			coremidi::source _source;
	//
	//			/* port */
	//			coremidi::output _port;
	//
	//			/* event list */
	//			coremidi::eventlist _eventlist;
	//
	//
	//			///* destination */
	//			//msh::midi::endpoint<"destination"> _destination;
	//			//
	//			///* packet */
	//			//msh::midi::packet _packet;
	//
	//	}; // class server
	//
	//} // namespace midi

} // namespace msh

#endif // MSH_APPLE

#endif // ___MSH_MIDI_SERVER_HPP___

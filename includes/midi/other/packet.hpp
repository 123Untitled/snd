#ifndef ___COREMIDI_PLUS_PLUS_EVENT_PACKET_HPP___
#define ___COREMIDI_PLUS_PLUS_EVENT_PACKET_HPP___

#include "msh/config/os.hpp"

#if defined(MSH_APPLE)

#include "coremidi++/types.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- E V E N T  N A M E S P A C E ----------------------------------------

	namespace event {


		// -- P A C K E T -----------------------------------------------------

		class packet final {

			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = coremidi::event::packet;


				// -- private members -----------------------------------------

				/* timestamp */
				coremidi::timestamp _timestamp;

				/* size */
				coremidi::u32 _size;

				/* words */
				coremidi::u32* _words;


			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				packet(void)
				: _timestamp{0U},
				  _size{0U},
				  _words{nullptr} {
				}

		}; // class packet

	} // namespace event

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___COREMIDI_PLUS_PLUS_EVENT_PACKET_HPP___

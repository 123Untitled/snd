#ifndef ___MSH_COREMIDI_DESTINATION_HPP___
#define ___MSH_COREMIDI_DESTINATION_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/object.hpp"
#include "midi/coremidi/client.hpp"
#include "midi/coremidi/types.hpp"

#include <iostream>



// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- D E S T I N A T I O N -----------------------------------------------

	class destination final : public coremidi::object {


		private:


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::destination;


			// -- private members ---------------------------------------------

			/* external */
			bool _external;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			destination(void) noexcept = default;

			/* id constructor */
			destination(const ::MIDIEndpointRef&);

			/* name constructor */
			destination(const coremidi::client&, const char*);

			/* deleted copy constructor */
			destination(const ___self&) = delete;

			/* move constructor */
			destination(___self&&) noexcept;

			/* destructor */
			~destination(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self&;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* read midi */
			static auto _read_midi(const ::MIDIEventList&) -> void;

	}; // class destination

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_DESTINATION_HPP___

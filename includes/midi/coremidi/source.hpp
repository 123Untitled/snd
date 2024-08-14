#ifndef ___MSH_COREMIDI_SOURCE_HPP___
#define ___MSH_COREMIDI_SOURCE_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/object.hpp"
#include "midi/coremidi/client.hpp"
#include "midi/coremidi/types.hpp"

#include <iostream>



// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	using midi_endpoint_reference = ::MIDIEndpointRef;


	// -- S O U R C E ---------------------------------------------------------

	class source final : public coremidi::object {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::source;


			// -- private members ---------------------------------------------

			/* external */
			bool _external;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			source(void) noexcept = default;

			/* id constructor */
			source(const ::MIDIEndpointRef&);

			/* name constructor */
			source(const coremidi::client&, const char*);

			/* deleted copy constructor */
			source(const ___self&) = delete;

			/* move constructor */
			source(___self&&) noexcept;

			/* destructor */
			~source(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self&;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;

	}; // class source

} // namespace coremidi


#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_SOURCE_HPP___

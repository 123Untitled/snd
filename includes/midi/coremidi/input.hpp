#ifndef ___MSH_COREMIDI_INPUT_HPP___
#define ___MSH_COREMIDI_INPUT_HPP___


#include "coremidi++/os.hpp"

#if defined(MSH_APPLE)

#include "coremidi++/string.hpp"
#include "coremidi++/client.hpp"
#include "coremidi++/destination.hpp"
#include "coremidi++/source.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- I N P U T -----------------------------------------------------------

	class input final : public coremidi::object {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::input;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			input(void) noexcept = default;

			/* client constructor */
			input(const coremidi::client& client, const char* name) {

				// create cfstring
				corefoundation::string cstr{name};

				// create input port
				const ::OSStatus result = ::MIDIInputPortCreateWithProtocol(
											client.id(),
											cstr,
											kMIDIProtocol_1_0,
											&_ref,
											^(const MIDIEventList*, void*) {
											});

				// check if port was created
				if (result != noErr)
					throw coremidi::exception{result, "error creating midi input port"};
			}

			/* deleted copy constructor */
			input(const ___self&) = delete;

			/* move constructor */
			input(___self&& other) noexcept
			: coremidi::object{other._ref} {

				// reset other
				other._ref = 0U;
			}

			/* destructor */
			~input(void) noexcept {

				// dispose port
				___self::_dispose();
			}


			// -- public assignment operators -----------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self& {

				// check self assignment
				if (this == &other)
					return *this;

				// dispose port
				___self::_dispose();

				// move port
				_ref       = other._ref;
				other._ref = 0U;

				return *this;
			}


			// -- public modifiers ----------------------------------------

			/* connect */
			auto connect(const coremidi::source& ep) -> void {

				// connect endpoint to port
				::OSStatus status = ::MIDIPortConnectSource(_ref, ep.id(), nullptr);

				if (status != noErr)
					throw coremidi::exception{status, "error connecting midi endpoint to port"};
			}

			/* disconnect */
			auto disconnect(const coremidi::source& ep) -> void {

				// disconnect endpoint from port
				::OSStatus status = ::MIDIPortDisconnectSource(_ref, ep.id());

				if (status != noErr)
					throw coremidi::exception{status, "error disconnecting midi endpoint from port"};
			}


		private:

			// -- private methods -----------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void {

				// check port validity
				if (_ref == 0U)
					return;

				// dispose port
				static_cast<void>(
						::MIDIPortDispose(_ref)
				);
			}

	}; // class input

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_INPUT_HPP___

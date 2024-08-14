#ifndef ___MSH_COREMIDI_OUTPUT_HPP___
#define ___MSH_COREMIDI_OUTPUT_HPP___


#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/corefoundation/string.hpp"
#include "midi/coremidi/client.hpp"
#include "midi/coremidi/destination.hpp"
#include "midi/coremidi/source.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- O U T P U T ---------------------------------------------------------

	class output final : public coremidi::object {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::output;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			output(void) noexcept = default;

			/* client constructor */
			output(const coremidi::client& client, const char* name) {

				// create cfstring
				corefoundation::string cstr{name};

				// create output port
				::OSStatus result = ::MIDIOutputPortCreate(client.id(), cstr, &_ref);

				// check if port was created
				if (result != noErr)
					throw coremidi::exception{result, "error creating midi output port"};
			}

			/* deleted copy constructor */
			output(const ___self&) = delete;

			/* move constructor */
			output(___self&& other) noexcept
			: coremidi::object{other._ref} {

				// reset other
				other._ref = 0U;
			}

			/* destructor */
			~output(void) noexcept {

				// dispose port
				___self::_dispose();
			}


			// -- public assignment operators ---------------------------------

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


		private:

			// -- private methods ---------------------------------------------

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


	}; // class output

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_OUTPUT_HPP___

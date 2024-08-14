#ifndef ___MSH_COREMIDI_CLIENT_HPP___
#define ___MSH_COREMIDI_CLIENT_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include "midi/coremidi/object.hpp"
#include <CoreMIDI/CoreMIDI.h>


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- C L I E N T ---------------------------------------------------------

	class client final : public coremidi::object {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::client;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			client(void) noexcept = default;

			/* name constructor */
			client(const char*);

			/* deleted copy constructor */
			client(const ___self&) = delete;

			/* move constructor */
			client(___self&&) noexcept;

			/* destructor */
			~client(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* _notification */
			static auto _notification(const ::MIDINotification*, void*) noexcept -> void;

	}; // class client

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_COREMIDI_CLIENT_HPP___

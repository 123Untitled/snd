#ifndef ___MSH_COREMIDI_EXCEPTION_HPP___
#define ___MSH_COREMIDI_EXCEPTION_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include <exception>
#include "midi/coremidi/types.hpp"
#include <CoreMIDI/CoreMIDI.h>


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- E X C E P T I O N ---------------------------------------------------

	class exception : public std::exception {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::exception;


			// -- private members ---------------------------------------------

			/* error code */
			cm::os_status _code;

			/* error message */
			const char* _what;


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			exception(void) noexcept = delete;

			/* code constructor */
			exception(const ::OSStatus code, const char* what) noexcept
			: std::exception{}, _code{code}, _what{what} {
			}

			/* copy constructor */
			exception(const ___self&) noexcept = default;

			/* move constructor */
			exception(___self&&) noexcept = default;

			/* destructor */
			~exception(void) noexcept override = default;


			// -- public operators --------------------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* code */
			auto code(void) const noexcept -> ::OSStatus {
				return _code;
			}

			/* what */
			auto what(void) const noexcept -> const char* override {
				return _what;
			}

	}; // class exception

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___COREMIDI_PLUS_PLUS_EXCEPTION_HPP___

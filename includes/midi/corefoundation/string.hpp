#ifndef ___MSH_COREFOUNDATION_STRING_HPP___
#define ___MSH_COREFOUNDATION_STRING_HPP___

#include "config/os.hpp"

#if defined(MSH_APPLE)

#include <CoreFoundation/CoreFoundation.h>


// -- forward declarations ----------------------------------------------------

namespace coremidi {
	class object;
}

// -- C O R E F O U N D A T I O N  N A M E S P A C E --------------------------

namespace corefoundation {


	// -- S T R I N G ---------------------------------------------------------

	class string final {


		// -- friends ---------------------------------------------------------

		/* object as friend */
		friend class coremidi::object;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = corefoundation::string;


			// -- private members ---------------------------------------------

			/* string */
			::CFStringRef _string;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			string(void) noexcept
			: _string{nullptr} {
			}

			/* string view constructor */
			string(const char* str)
			: _string{::CFStringCreateWithCString(kCFAllocatorDefault,
												  str,
												  kCFStringEncodingASCII)} {

				// check if string was created
				if (_string == nullptr)
					throw "error creating string";
			}

			/* copy constructor */
			string(const ___self& other)
			: _string{::CFStringCreateCopy(kCFAllocatorDefault, other._string)} {

				// check if string was created
				if (_string == nullptr)
					throw "error creating string";
			}

			/* move constructor */
			string(___self&& other) noexcept
			: _string{other._string} {
				other._string = nullptr;
			}

			/* destructor */
			~string(void) noexcept {
				// release string
				if (_string == nullptr)
					return;
				::CFRelease(_string);
			}


			// -- public accessors --------------------------------------------

			/* length */
			auto length(void) const -> ::CFIndex {
				return ::CFStringGetLength(_string);
			}


			// -- public conversion operators ---------------------------------

			/* ::CFStringRef conversion operator */
			operator ::CFStringRef(void) const noexcept {
				return _string;
			}


	}; // class string

} // namespace corefoundation


#endif // MSH_APPLE

#endif // ___MSH_COREFOUNDATION_STRING_HPP___

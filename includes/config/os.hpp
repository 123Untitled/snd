#ifndef ___MSH_OS_HPP___
#define ___MSH_OS_HPP___


// -- operating system check --------------------------------------------------

/* linux */
#if defined(__linux__)
#	define MSH_LINUX

/* bsd */
#elif defined(__unix__) || (!defined(__APPLE__) && defined(__MACH__))
#	if defined(BSD)
#		define MSH_BSD
#	endif

/* apple */
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)

#	define MSH_APPLE

#endif

#endif // ___MSH_OS_HPP___

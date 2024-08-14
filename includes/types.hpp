#ifndef ___SND_TYPES_HPP___
#define ___SND_TYPES_HPP___

#include <cstdint>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	/* size_t type */
	using size_t = decltype(sizeof(0));

	/* 8-bit unsigned integer */
	using u8 = unsigned char;

	/* 16-bit unsigned integer */
	using u16 = std::uint16_t;

	/* 32-bit unsigned integer */
	using u32 = std::uint32_t;

	/* 64-bit unsigned integer */
	using u64 = std::uint64_t;

	/* 8-bit signed integer */
	using i8 = std::int8_t;

	/* 16-bit signed integer */
	using i16 = std::int16_t;

	/* 32-bit signed integer */
	using i32 = std::int32_t;

	/* 64-bit signed integer */
	using i64 = std::int64_t;

} // namespace snd

#endif // ___SND_TYPES_HPP___

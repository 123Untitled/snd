#ifndef ___SND_STRING_HPP___
#define ___SND_STRING_HPP___

#include "types.hpp"


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- C O P Y -------------------------------------------------------------

	namespace ___impl {

		/* copy implementation */
		template <typename T, decltype(sizeof(0)) D, decltype(D) S, decltype(S) I>
		constexpr auto ___copy(T (&dst)[D], const T (&src)[S]) noexcept -> void {
			if constexpr (I == D or I == S){
				return;
			} else {
				dst[I] = src[I];
				snd::___impl::___copy<T, D, S, I + 1>(dst, src);
			}
		}

	}

	/* copy */
	template <typename ___type, snd::size_t ___ds, snd::size_t ___ss>
	constexpr auto copy(___type (&___dst)[___ds], const ___type (&___src)[___ss]) noexcept -> void {
		snd::___impl::___copy<___type, ___ds, ___ss, 0U>(___dst, ___src);
	}


	// -- C O M P A R E -------------------------------------------------------


	namespace ___impl {

		/* compare implementation */
		template <snd::size_t S, snd::size_t I>
		constexpr auto ___compare(const char (&lhs)[S], const char (&rhs)[S]) noexcept -> signed int {
			if constexpr (I == S) {
				return 0;
			} else {
				return (lhs[I] == rhs[I])
					 ? (snd::___impl::___compare<S, I + 1>(lhs, rhs))
					 : (lhs[I] > rhs[I] ? +1 : -1);
			}
		}

	}

	/* compare */
	template <snd::size_t L, snd::size_t R>
	constexpr auto compare(const char (&lhs)[L], const char (&rhs)[R]) noexcept -> signed int {

		// check for equal size
		if constexpr (L == R)
			return snd::___impl::___compare<L, 0U>(lhs, rhs);
		else
			return (L > R ? +1U : -1U);
	}



	// -- B A S I C  S T R I N G  L I T E R A L -------------------------------

	template <snd::size_t ___size>
	struct string final {


		// -- assertions ------------------------------------------------------

		/* check for zero size */
		static_assert(___size > 1U, "empty string"); // assume null-terminated


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::string<___size>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = char;

			/* const reference type */
			using const_reference = const value_type(&)[___size];

			/* size type */
			using size_type       = decltype(___size);


			// -- public members ----------------------------------------------

			/* data */
			value_type _data[___size];


			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			string(void) = delete;

			/* array constructor */
			template <size_type ___sz>
			consteval string(const value_type (&___str)[___sz]) noexcept
			: _data{} {
				snd::copy(_data, ___str);
			}


			/* copy constructor */
			consteval string(const ___self&) noexcept = default;

			/* move constructor */
			consteval string(___self&&) noexcept = default;

			/* destructor */
			constexpr ~string(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			consteval auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			consteval auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* data */
			consteval auto data(void) const noexcept -> const_reference {
				return _data;
			}

			/* size */
			consteval auto size(void) const noexcept -> size_type {
				return ___size - 1U; // assume null-terminated
			}


			// -- public conversion operators ---------------------------------

			/* const reference conversion operator */
			constexpr operator const_reference(void) const noexcept {
				return _data;
			}


			// -- public comparison operators ---------------------------------

			/* equality operator */
			template <size_type __size>
			consteval auto operator==(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) == 0;
			}

			/* inequality operator */
			template <size_type __size>
			consteval auto operator!=(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) != 0;
			}

			/* less than operator */
			template <size_type __size>
			consteval auto operator<(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) < 0;
			}

			/* greater than operator */
			template <size_type __size>
			consteval auto operator>(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) > 0;
			}

			/* less than or equal to operator */
			template <size_type __size>
			consteval auto operator<=(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) <= 0;
			}

			/* greater than or equal to operator */
			template <size_type __size>
			consteval auto operator>=(const snd::string<__size>& other) const noexcept -> bool {
				return snd::compare(_data, other._data) >= 0;
			}

	};


	// -- deduction guides ----------------------------------------------------

	template <snd::size_t ___size>
	string(const char (&)[___size]) -> string<___size>;




	/* equality operator */
	template <snd::size_t L, snd::size_t R>
	consteval auto operator==(const snd::string<L>& lhs,
							  const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) == 0;
	}

	/* equality operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	consteval auto operator==(const char (&lhs)[L],
							  const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) == 0;
	}



	/* inequality operator */
	template <snd::size_t L, snd::size_t R>
	consteval auto operator!=(const snd::string<L>& lhs,
							  const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) != 0;
	}

	/* inequality operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator!=(const char (&lhs)[L],
							  const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) != 0;
	}



	/* less than operator */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator<(const snd::string<L>& lhs,
							 const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) < 0;
	}

	/* less than operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator<(const char (&lhs)[L],
							 const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) < 0;
	}




	/* greater than operator */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator>(const snd::string<L>& lhs,
							 const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) > 0;
	}

	/* greater than operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator>(const char (&lhs)[L],
							 const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) > 0;
	}




	/* less than or equal to operator */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator<=(const snd::string<L>& lhs,
							  const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) <= 0;
	}

	/* less than or equal to operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator<=(const char (&lhs)[L],
							  const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) <= 0;
	}




	/* greater than or equal to operator */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator>=(const snd::string<L>& lhs,
							  const char (&rhs)[R]) noexcept -> bool {
		return snd::compare(lhs._data, rhs) >= 0;
	}

	/* greater than or equal to operator (reverse) */
	template <snd::size_t L, snd::size_t R>
	constexpr auto operator>=(const char (&lhs)[L],
							  const snd::string<R>& rhs) noexcept -> bool {
		return snd::compare(lhs, rhs._data) >= 0;
	}


} // namespace snd

#endif // ___SND_STRING_HPP___

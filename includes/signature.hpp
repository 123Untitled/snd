#ifndef ___SND_TIME_SIGNATURE_HPP___
#define ___SND_TIME_SIGNATURE_HPP___

#include "types.hpp"
#include <iostream>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- S I G N A T U R E ---------------------------------------------------

	class signature final {

		public:

			// -- public types ------------------------------------------------

			/* integer type */
			using size_type = snd::size_t;


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::signature;


			// -- private members ---------------------------------------------

			/* numerator */
			size_type _numerator;

			/* denominator */
			size_type _denominator;

			/* modulus */
			size_type _modulus;

#define MIDI_PPQN 24U

			// -- private methods ---------------------------------------------

			/* compute modulus */
			auto _compute_modulus(void) const noexcept -> size_type {
				return (_numerator * MIDI_PPQN * 4U) / _denominator;
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			signature(void) noexcept
			: _numerator{1U}, _denominator{16U},
			  _modulus{___self::_compute_modulus()} {
			}

			/* constructor */
			signature(const size_type& ___nu, const size_type& ___de) noexcept
			: _numerator{___nu}, _denominator{___de},
			  _modulus{___self::_compute_modulus()} {
			}

			/* copy constructor */
			signature(const ___self&) noexcept = default;

			/* move constructor */
			signature(___self&&) noexcept = default;

			/* destructor */
			~signature(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* numerator */
			auto numerator(void) const noexcept -> const size_type& {
				return _numerator;
			}

			/* denominator */
			auto denominator(void) const noexcept -> const size_type& {
				return _denominator;
			}

			/* modulus */
			auto modulus(void) const noexcept -> const size_type& {
				return _modulus;
			}

			/* is time */
			auto is_time(const size_type& ___cn) const noexcept -> bool {
				return (___cn % _modulus) == 0U;
			}

			/* count */
			auto count(const size_type& ___cn) const noexcept -> size_type {
				return ___cn / _modulus;
			}


			// -- public modifiers --------------------------------------------

			/* numerator */
			auto numerator(const size_type& ___nu) noexcept -> void {
				_numerator = ___nu;
				_modulus = ___self::_compute_modulus();
			}

			/* denominator */
			auto denominator(const size_type& ___de) noexcept -> void {
				_denominator = ___de;
				_modulus = ___self::_compute_modulus();
			}


			// -- public comparison operators ---------------------------------

			/* equal */
			auto operator==(const ___self& other) const noexcept -> bool {
				return _modulus == other._modulus;
			}

			/* not equal */
			auto operator!=(const ___self& other) const noexcept -> bool {
				return _modulus != other._modulus;
			}

			/* less than */
			auto operator<(const ___self& other) const noexcept -> bool {
				return _modulus < other._modulus;
			}

			/* less than or equal */
			auto operator<=(const ___self& other) const noexcept -> bool {
				return _modulus <= other._modulus;
			}

			/* greater than */
			auto operator>(const ___self& other) const noexcept -> bool {
				return _modulus > other._modulus;
			}

			/* greater than or equal */
			auto operator>=(const ___self& other) const noexcept -> bool {
				return _modulus >= other._modulus;
			}

	}; // class signature

} // namespace snd


// -- non-member functions ----------------------------------------------------

/* output stream operator */
inline auto operator<<(std::ostream& os, const snd::signature& sign) -> std::ostream& {
	os << sign.numerator() << '/' << sign.denominator() << " [" << sign.modulus() << ']';
	return os;
}

#endif // ___SND_TIME_SIGNATURE_HPP___

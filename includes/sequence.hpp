#ifndef ___SND_SEQUENCE_HPP___
#define ___SND_SEQUENCE_HPP___

#include "types.hpp"
#include "signature.hpp"

#include <vector>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- S E Q U E N C E -----------------------------------------------------

	template <typename ___type>
	class sequence {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::sequence<___type>;


			// -- private members ---------------------------------------------

			/* sequence */
			std::vector<___type> _seq;

			/* signature */
			snd::signature _sig;

			/* current */
			___type _current;

			/* modified */
			___type _modified;

		protected:

			// -- protected lifecycle -----------------------------------------

			/* default value constructor */
			sequence(const ___type& ___vl)
			: _seq{}, _sig{}, _current{___vl}, _modified{___vl} {

				_seq.reserve(0x01);
				_seq.push_back(___vl);
			}


		public:

			// -- public lifecycle --------------------------------------------

			/* deleted default constructor */
			sequence(void) = delete;

			/* copy constructor */
			sequence(const ___self&) = default;

			/* move constructor */
			sequence(___self&&) noexcept = default;

			/* destructor */
			virtual ~sequence(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public modifiers --------------------------------------------

			/* signature */
			auto signature(const snd::size_t& num, const snd::size_t& den) noexcept -> ___self& {
				_sig = snd::signature{num, den};
				return *this;
			}

			/* insert */
			template <typename... ___params>
			auto insert(const ___params&... ___args) -> ___self& {
				_seq.assign({_clamp(static_cast<___type>(___args))...});
				return *this;
			}

			/* current */
			auto current(const ___type& value) noexcept -> ___self& {
				_current = _clamp(value);
				return *this;
			}

			/* modified */
			auto modified(const ___type& value) noexcept -> ___self& {
				_modified = _clamp(value);
				return *this;
			}


			// -- public accessors --------------------------------------------

			/* signature */
			auto signature(void) const noexcept -> const snd::signature& {
				return _sig;
			}

			/* current */
			auto current(void) const noexcept -> const ___type& {
				return _current;
			}

			/* modified */
			auto modified(void) const noexcept -> const ___type& {
				return _modified;
			}


			// -- public methods ----------------------------------------------

			/* update */
			auto update(const snd::size_t& timeline) noexcept -> void {

				if (not _sig.is_time(timeline))
					return;

				_current = _seq[_sig.count(timeline) % _seq.size()];
				_modified = _current;
			}


		private:

			// -- private methods ---------------------------------------------

			/* clamp */
			virtual auto _clamp(const ___type&) const noexcept -> ___type = 0;

	}; // class sequence

} // namespace snd

#endif // ___SND_SEQUENCE_HPP___

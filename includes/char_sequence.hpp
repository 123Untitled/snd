#ifndef ___SND_CHAR_SEQUENCE_HPP___
#define ___SND_CHAR_SEQUENCE_HPP___

#include "types.hpp"
#include "string.hpp"


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- C H A R A C T E R  S E Q U E N C E ----------------------------------

	template <char... ___chars>
	class char_sequence final {


		private:

			// -- public types ------------------------------------------------

			/* self type */
			using ___self = snd::char_sequence<___chars...>;


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type = char;

			/* size type */
			using size_type = snd::size_t;


			// -- public accessors --------------------------------------------

			/* size */
			static consteval auto size(void) noexcept -> size_type {
				return sizeof...(___chars);
			}

	}; // class character_sequence


	// -- M A K E  C H A R A C T E R  S E Q U E N C E -------------------------

	namespace ___impl {


		/* make character sequence */
		template <snd::string ___str>
		class ___make_char_sequence final {


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = snd::___impl::___make_char_sequence<___str>;


			public:

				// -- public types --------------------------------------------

				/* value type */
				using value_type = typename decltype(___str)::value_type;

				/* size type */
				using size_type = typename decltype(___str)::size_type;


				// -- public lifecycle ----------------------------------------

				/* deleted default constructor */
				___make_char_sequence(void) = delete;

				/* deleted copy constructor */
				___make_char_sequence(const ___self&) = delete;

				/* deleted move constructor */
				___make_char_sequence(___self&&) = delete;

				/* deleted destructor */
				~___make_char_sequence(void) = delete;

				/* deleted copy assignment operator */
				auto operator=(const ___self&) -> ___self& = delete;

				/* deleted move assignment operator */
				auto operator=(___self&&) -> ___self& = delete;


			private:

				// -- private implementation ----------------------------------

				/* forward declaration */
				template <size_type, value_type...>
				struct ___;

				/* specialization for I == E, end of recursion */
				template <size_type ___idx, value_type... ___seq> requires (___idx == ___str.size())
				struct ___<___idx, ___seq...> final {
					using ___type = snd::char_sequence<___seq...>;
				};

				/* specialization for I < E, continue recursion */
				template <size_type ___idx, value_type... ___seq> requires (___idx < ___str.size())
				struct ___<___idx, ___seq...> final {
					using ___type = typename ___<___idx + 1U, ___seq..., ___str._data[___idx]>::___type;
				};


			public:

				// -- public types --------------------------------------------

				/* character sequence type */
				using type = typename ___self::___<0U>::___type;

		}; // class ___make_char_sequence

	} // namespace ___impl


	// -- make sequence aliases -----------------------------------------------

	/* make character sequence */
	template <snd::string ___str> // here i removed the size() - 1, because it was causing a bug
	using make_char_sequence = typename snd::___impl::___make_char_sequence<___str>::type;

} // namespace snd

#endif // ___SND_CHAR_SEQUENCE_HPP___

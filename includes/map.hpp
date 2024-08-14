#ifndef ___SND_MAP_HPP___
#define ___SND_MAP_HPP___

#include "string.hpp"
#include "types.hpp"
#include "char_sequence.hpp"

#include <type_traits>


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- L I T E R A L  M A P ------------------------------------------------

	template <typename ___type, snd::string... ___keys>
	class map final {


		private:

			// -- forward declarations ----------------------------------------

			template <typename>
			struct ___wrapper;


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::map<___type, ___keys...>;

			/* key type */
			template <snd::string ___k>
			using ___key = snd::make_char_sequence<___k>;

			/* wrapper from type */
			template <snd::string ___k>
			using ___wrapper_from = ___wrapper<___key<___k>>;


			// -- private constants -------------------------------------------

			/* have key */
			template <snd::string ___k>
			static constexpr bool ___have_key = true;//snd::is_one_of<___key<___k>, ___key<___keys>...>;


		// -- assertions ------------------------------------------------------

		///* check all string literals are unique */
		//static_assert(xns::is_all_unique<___key<___literals>...>,
		//			 "literal_map: all string literals must be unique");
		//
		///* check for map size */
		//static_assert(sizeof...(___literals) > 0,
		//			"Map must have at least one element.");


		public:

			// -- public types ------------------------------------------------

			/* value type */
			using value_type      = ___type;

			/* reference type */
			using reference       = value_type&;

			/* const reference type */
			using const_reference = const value_type&;

			/* size type */
			using size_type       = snd::size_t;


		private:

			// -- private structs ---------------------------------------------

			/* __element */
			template <typename ___sequence>
			struct ___wrapper {

				// -- members -------------------------------------------------

				/* value */
				value_type value;

			}; // struct __element


			/* __impl */
			struct ___impl final : public ___wrapper<___key<___keys>>... {


				// -- types ---------------------------------------------------

				/* self type */
				using ___self = ___self::___impl;


				// -- lifecycle -----------------------------------------------

				/* default constructor */
				constexpr ___impl(void) noexcept
				: ___wrapper<___key<___keys>>{}... {
				}

				/* variadic constructor */
				template <typename... ___params> requires (sizeof...(___params) > 1)
				constexpr ___impl(___params&&... ___args) noexcept
				: ___wrapper<___key<___keys>>{std::forward<___params>(___args)}... {
				}

				/* copy constructor */
				constexpr ___impl(const ___self&) noexcept = default;

				/* move constructor */
				constexpr ___impl(___self&&) noexcept = default;

				/* destructor */
				constexpr ~___impl(void) noexcept = default;


				// -- assignment operators ------------------------------------

				/* copy assignment operator */
				auto operator=(const ___self&) noexcept -> ___self& = default;

				/* move assignment operator */
				auto operator=(___self&&) noexcept -> ___self& = default;

			}; // struct ___impl


			// -- private members ---------------------------------------------

			/* implementation */
			___impl _impl;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			constexpr map(void) noexcept
			: _impl{} {
			}

			/* variadic constructor */
			template <typename... ___params>
			constexpr map(___params&&... ___args) requires (sizeof...(___args) > 1U)
			: _impl{std::forward<___params>(___args)...} {

				static_assert(sizeof...(___keys) == sizeof...(___args),
							"must have exactly one value for each key.");
			}

			/* copy constructor */
			constexpr map(const ___self&) noexcept = default;

			/* move constructor */
			constexpr map(___self&&) noexcept = default;

			/* destructor */
			constexpr ~map(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			constexpr auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			constexpr auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* size */
			constexpr auto size(void) const noexcept -> size_type {
				return sizeof...(___keys);
			}

			/* contains */
			constexpr auto contains(const_reference ___vl) const noexcept -> bool {
				return ((___vl == static_cast<___wrapper_from<___keys>&>(_impl).value) || ...);
			}


			// -- public loopers ----------------------------------------------

			/* for each element */
			template <typename ___invokable, typename... ___params>
			constexpr auto for_each(___invokable&& ___func, ___params&&... ___args) -> void {
				(___func(static_cast<___wrapper_from<___keys>&>(_impl).value, std::forward<___params>(___args)...), ...);
			}

			/* for each const element */
			template <typename ___invokable, typename... ___params>
			constexpr auto for_each(___invokable&& ___func, ___params&&... ___args) const -> void {
				(___func(static_cast<const ___wrapper_from<___keys>&>(_impl).value, std::forward<___params>(___args)...), ...);
			}


		// -- friends ---------------------------------------------------------

		/* get as friend */
		template <snd::string, typename ___tp, snd::string... ___ks>
		friend constexpr auto get(snd::map<___tp, ___ks...>&) noexcept -> ___tp&;

		/* get as friend */
		template <snd::string, typename ___tp, snd::string... ___ks>
		friend constexpr auto get(snd::map<___tp, ___ks...>&&) noexcept -> ___tp&&;

		/* get as friend */
		template <snd::string, typename ___tp, snd::string... ___ks>
		friend constexpr auto get(const snd::map<___tp, ___ks...>&) noexcept -> const ___tp&;

		/* get as friend */
		template <snd::string, typename ___tp, snd::string... ___ks>
		friend constexpr auto get(const snd::map<___tp, ___ks...>&&) noexcept -> const ___tp&&;

	}; // class map


	/* get */
	template <snd::string ___key, typename ___type, snd::string... ___keys>
	constexpr auto get(snd::map<___type, ___keys...>& ___map) noexcept -> ___type& {

		// map type
		using ___map_type = snd::map<___type, ___keys...>;

		// assertions
		static_assert(___map_type::template ___have_key<___key>, "key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___key>;

		// return lvalue reference
		return static_cast<___type&>(static_cast<___wrapper_type&>(___map._impl).value);
	}

	/* get */
	template <snd::string ___key, typename ___type, snd::string... ___keys>
	constexpr auto get(snd::map<___type, ___keys...>&& ___map) noexcept -> ___type&& {

		// map type
		using ___map_type = snd::map<___type, ___keys...>;

		// assertions
		static_assert(___map_type::template ___have_key<___key>, "key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___key>;

		// return rvalue reference
		return static_cast<___type&&>(static_cast<___wrapper_type&&>(___map._impl).value);
	}

	/* get */
	template <snd::string ___key, typename ___type, snd::string... ___keys>
	constexpr auto get(const snd::map<___type, ___keys...>& ___map) noexcept -> const ___type& {

		// map type
		using ___map_type = snd::map<___type, ___keys...>;

		// assertions
		static_assert(___map_type::template ___have_key<___key>, "key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___key>;

		// return const lvalue reference
		return static_cast<const ___type&>(static_cast<const ___wrapper_type&>(___map._impl).value);
	}

	/* get */
	template <snd::string ___key, typename ___type, snd::string... ___keys>
	constexpr auto get(const snd::map<___type, ___keys...>&& ___map) noexcept -> const ___type&& {

		// map type
		using ___map_type = snd::map<___type, ___keys...>;

		// assertions
		static_assert(___map_type::template ___have_key<___key>, "key not found");

		// wrapper type
		using ___wrapper_type = typename ___map_type::template ___wrapper_from<___key>;

		// return const rvalue reference
		return static_cast<const ___type&&>(static_cast<const ___wrapper_type&&>(___map._impl).value);
	}



	/* for each */
	template <typename ___invokable, typename ___type, snd::string... ___keys, typename... ___params>
	constexpr auto for_each(snd::map<___type, ___keys...>& ___map, ___invokable&& ___func, ___params&&... ___args) -> void {
		___map.for_each(std::forward<___invokable>(___func), std::forward<___params>(___args)...);
	}

	/* for each */
	template <typename ___invokable, typename ___type, snd::string... ___keys, typename... ___params>
	constexpr auto for_each(const snd::map<___type, ___keys...>& ___map, ___invokable&& ___func, ___params&&... ___args) -> void {
		___map.for_each(std::forward<___invokable>(___func), std::forward<___params>(___args)...);
	}

} // namespace snd

#endif // ___SND_MAP_HPP___

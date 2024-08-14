#ifndef ___SND_TRIGGERS_HPP___
#define ___SND_TRIGGERS_HPP___

#include "sequence.hpp"


// -- S N D  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- T R I G G E R S -----------------------------------------------------

	class triggers final : public snd::sequence<bool> {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::triggers;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			triggers(void)
			: snd::sequence<bool>(false) {
			}

			/* copy constructor */
			triggers(const ___self&) = default;

			/* move constructor */
			triggers(___self&&) noexcept = default;

			/* destructor */
			~triggers(void) = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


		private:

			// -- private overrides -------------------------------------------

			/* clamp */
			auto _clamp(const bool& ___vl) const noexcept -> bool override {
				return ___vl;
			}

	}; // class triggers

} // namespace snd

#endif // ___SND_TRIGGERS_HPP___

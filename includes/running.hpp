#ifndef ___MSH_RUNNING_HPP___
#define ___MSH_RUNNING_HPP___


// -- M S H  N A M E S P A C E ------------------------------------------------

namespace snd {


	// -- R U N N I N G -------------------------------------------------------

	class running final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = snd::running;


			// -- private members ---------------------------------------------

			/* running */
			bool _running;


			// -- private lifecycle -------------------------------------------

			/* default constructor */
			running(void) noexcept
			: _running{false} {
			}

			/* deleted copy constructor */
			running(const ___self&) = delete;

			/* deleted move constructor */
			running(___self&&) = delete;

			/* destructor */
			~running(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* deleted move assignment operator */
			auto operator=(___self&&) -> ___self& = delete;


			// -- private static methods --------------------------------------

			/* shared */
			static auto _shared(void) noexcept -> ___self& {
				static ___self _instance;
				return _instance;
			}


		public:

			// -- public static methods ---------------------------------------

			/* start */
			static auto start(void) noexcept -> void {
				___self::_shared()._running = true;
			}

			/* stop */
			static auto stop(void) noexcept -> void {
				___self::_shared()._running = false;
			}

			/* toggle */
			static auto toggle(void) noexcept -> void {
				___self::_shared()._running ^= true;
			}

			/* state */
			static auto state(void) noexcept -> bool {
				return ___self::_shared()._running;
			}

	}; // class running

} // namespace msh

#endif // ___MSH_RUNNING_HPP___

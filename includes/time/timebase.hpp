#ifndef ___MSH_TIME_TIMEBASE_HPP___
#define ___MSH_TIME_TIMEBASE_HPP___




// -- M S H  N A M E S P A C E ------------------------------------------------

namespace msh {


	// -- T I M E B A S E -----------------------------------------------------

	class timebase final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = msh::timebase;


			// -- private members ---------------------------------------------

			/* milliseconds to absolute clock */
			double _ms_to_absolute;

			/* absolute clock to nanoseconds */
			double _absolute_to_nano;

			/* nanoseconds to absolute clock */
			double _nano_to_absolute;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			timebase(void);

			/* copy constructor */
			timebase(const ___self&) noexcept = default;

			/* move constructor */
			timebase(___self&&) noexcept = default;

			/* destructor */
			~timebase(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			auto operator=(const ___self&) noexcept -> ___self& = default;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self& = default;


			// -- public accessors --------------------------------------------

			/* ms to absolute */
			auto ms_to_absolute(void) const noexcept -> double;

			/* absolute to nano */
			auto absolute_to_nano(void) const noexcept -> double;

			/* nano to absolute */
			auto nano_to_absolute(void) const noexcept -> double;

	}; // class timebase

} // namespace msh

#endif // ___MSH_TIME_TIMEBASE_HPP___

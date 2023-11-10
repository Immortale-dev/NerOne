#ifndef NN_NERVALUE
#define NN_NERVALUE

#include "nerhelp.hpp"

namespace nerone {
	/**
	 * Class extends basic Value class and additionally defines
	 * gradient functions that can be used in Gradient Descent back
	 * propagation algorithm.
	 */
	class Value {
		public:
			Value() = default;
			virtual ~Value() = default;
			Value(data_t val);
			virtual data_t get();
			virtual void set(data_t val);

		protected:
			data_t val;
	};
}

#endif // NN_NERVALUE

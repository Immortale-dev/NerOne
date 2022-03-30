#ifndef NN_ACTIVATIONS_ELU
#define NN_ACTIVATIONS_ELU

#include <algorithm>
#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	namespace activations {
		/**
		 * Parametric Exponential Linear Unit activation function. For
		 * values less than 0, the result goes to -1 softly. Parameter
		 * decides the curve line for negative values. For values
		 * greater than 0, the result doesn't change.
		 *
		 * R should implement std::ratio class.
		 *
		 *                   /
		 *                 /
		 *  0 .........../
		 * -1 _________/
		 *             0
		 */
		template<typename R>
		class ELU {
			public:
				inline static value_t fun(value_t val) {
					return std::max(val, rat * (std::exp(val) - 1));
				}
				inline static value_t grad(value_t val) {
					return val >= 0 ? 1 : rat * std::exp(val);
				}

			private:
				constexpr static value_t rat = (value_t)R::num / (value_t)R::den;
		};
	}
}

#endif // NN_ACTIVATIONS_ELU

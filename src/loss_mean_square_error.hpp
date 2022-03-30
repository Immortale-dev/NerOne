#ifndef NN_LOSS_MEAN_SQUARE_ERROR
#define NN_LOSS_MEAN_SQUARE_ERROR

#include "nerhelp.hpp"

namespace nerone {
	namespace loss {
		/**
		 * Mean squared error (MSE) is the most commonly used loss
		 * function for regression. The loss is the mean overseen data
		 * of the squared differences between true and predicted values.
		 */
		class MeanSquareError {
			public:
				inline static value_t fun(value_t actual, value_t expected) {
					return (value_t)0.5 * (actual - expected) * (actual - expected);
				}
				inline static value_t grad(value_t actual, value_t expected) {
					return actual - expected;
				}
		};
	}
}

#endif // NN_LOSS_MEAN_SQUARE_ERROR

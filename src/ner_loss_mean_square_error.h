#ifndef _NN_NER_LOSS_MEAN_SQUARE_ERROR
#define _NN_NER_LOSS_MEAN_SQUARE_ERROR

#include "ner_help.h"

namespace nerone {
	namespace loss {
		/**
		 * Mean squared error (MSE) is the most commonly used loss
		 * function for regression. The loss is the mean overseen data
		 * of the squared differences between true and predicted values.
		 */
		class MeanSquareError {
			public:
				template<typename value_t>
				inline static value_t fun(value_t actual, value_t expected) {
					return (value_t)0.5 * (actual - expected) * (actual - expected);
				}
				template<typename value_t>
				inline static value_t grad(value_t actual, value_t expected) {
					return actual - expected;
				}
		};
	}
}

#endif // _NN_NER_LOSS_MEAN_SQUARE_ERROR

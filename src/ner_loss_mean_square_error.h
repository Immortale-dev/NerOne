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
				template<typename FT>
				inline static FT fun(FT actual, FT expected) {
					return (FT)0.5 * (actual - expected) * (actual - expected);
				}
				template<typename FT>
				inline static FT grad(FT actual, FT expected) {
					
					return actual - expected;
				}
		};
	}
}

#endif // _NN_NER_LOSS_MEAN_SQUARE_ERROR

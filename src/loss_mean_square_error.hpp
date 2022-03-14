#ifndef NN_LOSS_MEAN_SQUARE_ERROR
#define NN_LOSS_MEAN_SQUARE_ERROR

#include "nerhelp.hpp"

namespace nerone {
	
	namespace loss {
		
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

#ifndef NN_LOSS_MEAN_SQUARE_ERROR
#define NN_LOSS_MEAN_SQUARE_ERROR

#include "nerhelp.hpp"

namespace nerone {
	
	namespace loss {
		
		class MeanSquareError {
			public:
				value_t fun(value_t actual, value_t expected);
				value_t grad(value_t actual, value_t expected);
		};
	}
}

#endif // NN_LOSS_MEAN_SQUARE_ERROR

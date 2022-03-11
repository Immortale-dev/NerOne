#ifndef NN_LOSS_CROSS_ENTROPY
#define NN_LOSS_CROSS_ENTROPY

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace loss {
		
		class CrossEntropy {
			public:
				value_t fun(value_t actual, value_t expected);
				value_t grad(value_t actual, value_t expected);
		};
	}
}

#endif // NN_LOSS_CROSS_ENTROPY

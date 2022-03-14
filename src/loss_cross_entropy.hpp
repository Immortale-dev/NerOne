#ifndef NN_LOSS_CROSS_ENTROPY
#define NN_LOSS_CROSS_ENTROPY

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace loss {
		
		class CrossEntropy {
			public:
				inline static value_t fun(value_t actual, value_t expected) {
					return -(expected * std::log(actual) + ((value_t)1 - expected) * std::log((value_t)1 - actual));
				}
				inline static value_t grad(value_t actual, value_t expected) {
					return (actual - expected) / (actual * ((value_t)1 - actual));
				}
		};
	}
}

#endif // NN_LOSS_CROSS_ENTROPY

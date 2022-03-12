#ifndef NN_ACTIVATIONS_RELU
#define NN_ACTIVATIONS_RELU

#include <algorithm>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace activations {
		
		class ReLU {
			public:
				inline static value_t fun(value_t val) {
					return std::max(val, (value_t)0);
				}
				inline static value_t grad(value_t val) {
					return val >= 0 ? 1 : 0;
				}
		};
	}
}

#endif // NN_ACTIVATIONS_RELU

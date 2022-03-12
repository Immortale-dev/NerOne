#ifndef NN_ACTIVATIONS_TANH
#define NN_ACTIVATIONS_TANH

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace activations {
		
		class TanH {
			public:
				inline static value_t fun(value_t val) {
					return (std::exp(val) - std::exp(-val)) / (std::exp(val) + std::exp(-val));
				}
				inline static value_t grad(value_t val) {
					return (value_t)1 - val*val;
				}
		};
	}
}

#endif // NN_ACTIVATIONS_TANH

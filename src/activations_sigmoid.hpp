#ifndef NN_ACTIVATIONS_SIGMOID
#define NN_ACTIVATIONS_SIGMOID

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace activations {
		
		class Sigmoid {
			public:
				inline static value_t fun(value_t val){
					return (value_t)1 / ((value_t)1 + std::exp(-val));
				}
				inline static value_t grad(value_t val) {
					return val * ((value_t)1 - val);
				}
		};
	}
}

#endif // NN_ACTIVATIONS_SIGMOID

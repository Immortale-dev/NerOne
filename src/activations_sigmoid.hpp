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
					value_t o_val = Sigmoid::fun(val);
					return o_val * ((value_t)1 - o_val);
				}
		};
	}
}

#endif // NN_ACTIVATIONS_SIGMOID

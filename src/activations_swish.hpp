#ifndef NN_ACTIVATIONS_SWISH
#define NN_ACTIVATIONS_SWISH

#include <cmath>

#include "nerhelp.hpp"
#include "activations_sigmoid.hpp"

namespace nerone {
	
	namespace activations {
		
		class Swish {
			public:
				inline static value_t fun(value_t val) {
					return val * Sigmoid::fun(val);
				}
				inline static value_t grad(value_t val) {
					value_t o_val = fun(val);
					return o_val + Sigmoid::fun(val) * (1-o_val);
				}
		};
	}
}

#endif // NN_ACTIVATIONS_SWISH

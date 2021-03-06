#ifndef NN_ACTIVATIONS_TANH
#define NN_ACTIVATIONS_TANH

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	namespace activations {
		/**
		 * The output of the tanh activation function is Zero centered;
		 * hence we can easily map the output values as strongly
		 * negative, neutral, or strongly positive. Usually used in
		 * hidden layers of a neural network.
		 */
		class TanH {
			public:
				inline static value_t fun(value_t val) {
					return (std::exp(val) - std::exp(-val)) / (std::exp(val) + std::exp(-val));
				}
				inline static value_t grad(value_t val) {
					value_t o_val = TanH::fun(val);
					return (value_t)1 - o_val*o_val;
				}
		};
	}
}

#endif // NN_ACTIVATIONS_TANH

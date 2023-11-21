#ifndef _NN_NER_ACTIVATION_TANH
#define _NN_NER_ACTIVATION_TANH

#include <cmath>

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * The output of the tanh activation function is Zero centered;
		 * hence we can easily map the output values as strongly
		 * negative, neutral, or strongly positive. Usually used in
		 * hidden layers of a neural network.
		 */
		class TanH {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return (std::exp(val) - std::exp(-val)) / (std::exp(val) + std::exp(-val));
				}
				template<typename FT>
				inline static FT grad(FT val) {
					FT o_val = TanH::fun(val);
					return (FT)1 - o_val*o_val;
				}
		};
	}
}

#endif // _NN_NER_ACTIVATION_TANH

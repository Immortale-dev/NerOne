#ifndef _NN_NER_ACTIVATION_SIGMOID
#define _NN_NER_ACTIVATION_SIGMOID

#include <cmath>

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * The sigmoid function is a logistic function, which means
		 * that, whatever you input, you get an output ranging between
		 * 0 and 1.
		 */
		class Sigmoid {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return (FT)1 / ((FT)1 + std::exp(-val));
				}
				template<typename FT>
				inline static FT grad(FT val) {
					FT o_val = Sigmoid::fun(val);
					return o_val * ((FT)1 - o_val);
				}
		};
	}
}

#endif // _NN_NER_ACTIVATION_SIGMOID

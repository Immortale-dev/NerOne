#ifndef _NN_NER_ACTIVATION_SWISH
#define _NN_NER_ACTIVATION_SWISH

#include <cmath>

#include "ner_help.h"
#include "ner_activation_sigmoid.h"

namespace nerone {
	namespace activation {
		/**
		 * Swish is a smooth, non-monotonic function that consistently
		 * matches or outperforms ReLU on deep networks applied to a
		 * variety of challenging domains such as Image classification
		 * and Machine translation.
		 */
		class Swish {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return val * Sigmoid::fun(val);
				}
				template<typename FT>
				inline static FT grad(FT val) {
					FT o_val = fun(val);
					return o_val + Sigmoid::fun(val) * (1-o_val);
				}
		};
	}
}

#endif // _NN_NER_ACTIVATION_SWISH

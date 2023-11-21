#ifndef _NN_NER_LOSS_CROSS_ENTROPY
#define _NN_NER_LOSS_CROSS_ENTROPY

#include <cmath>

#include "nerhelp.hpp"

namespace nerone {
	namespace loss {
		/**
		 * Cross-entropy loss, or log loss, measures the performance of
		 * a classification model whose output is a probability value
		 * between 0 and 1. Cross-entropy loss increases as the
		 * predicted probability diverges from the actual label.
		 */
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

#endif // _NN_NER_LOSS_CROSS_ENTROPY

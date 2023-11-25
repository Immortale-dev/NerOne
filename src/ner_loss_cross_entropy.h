#ifndef _NN_NER_LOSS_CROSS_ENTROPY
#define _NN_NER_LOSS_CROSS_ENTROPY

#include <cmath>

#include "ner_help.h"

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
				template<typename FT>
				inline static FT fun(FT actual, FT expected) {
					return -(expected * std::log(actual) + ((FT)1 - expected) * std::log((FT)1 - actual));
				}
				template<typename FT>
				inline static FT grad(FT actual, FT expected) {
					return (actual - expected) / (actual * ((FT)1 - actual));
				}
		};
	}
}

#endif // _NN_NER_LOSS_CROSS_ENTROPY

#ifndef _NN_NER_ACTIVATION_SELU
#define _NN_NER_ACTIVATION_SELU

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * Scaled Exponential Linear Unit. This activation functions is
		 * one of the newer one's.
		 */
		class SELU {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return lambda * (val > 0 ? val : alpha * std::exp(val) - alpha);
				}
				template<typename FT>
				inline static FT grad(FT val) {
					return lambda * (val > 0 ? 1 : alpha * std::exp(val));
				}

			private:
				static constexpr long double alpha = 1.6732632423543772848170429916717L;
				static constexpr long double lambda = 1.0507009873554804934193349852946L;
		};
	}
}

#endif // _NN_NER_ACTIVATION_SELU

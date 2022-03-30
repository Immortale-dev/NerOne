#ifndef NN_ACTIVATIONS_SELU
#define NN_ACTIVATIONS_SELU

#include "nerhelp.hpp"

namespace nerone {
	namespace activations {
		/**
		 * Scaled Exponential Linear Unit. This activation functions is
		 * one of the newer one's.
		 */
		class SELU {
			public:
				inline static value_t fun(value_t val) {
					return lambda * (val > 0 ? val : alpha * std::exp(val) - alpha);
				}
				inline static value_t grad(value_t val) {
					return lambda * (val > 0 ? 1 : alpha * std::exp(val));
				}

			private:
				static constexpr value_t alpha = 1.6732632423543772848170429916717;
				static constexpr value_t lambda = 1.0507009873554804934193349852946;
		};
	}
}

#endif // NN_ACTIVATIONS_SELU

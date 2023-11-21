#ifndef _NN_NER_ACTIVATION_GELU
#define _NN_NER_ACTIVATION_GELU

#include <cmath>

#include "ner_help.h"
#include "ner_activation_tanh.h"

namespace nerone {
	namespace activation {
		/**
		 * Gaussian Error Linear Unit activation function. For values
		 * much less than 0, the result equals 0, but for values
		 * slightly less than 0, the result slightly less than 0. For
		 * values greater than 0 the result doesn't change.
		 *
		 *                   /
		 *                 /
		 *               /
		 *  0 _________/
		 *             0
		 */
		class GELU {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return (FT)0.5 * val * ((FT)1 + TanH::fun(sq2DivPi() * (val + (FT)0.044715 * val * val * val)));
				}
				template<typename FT>
				inline static FT grad(FT val) {
					FT p_val = (FT)0.0356774 * val * val * val + (FT)0.797885 * val;
					FT p_sech = (FT)1 / std::cosh(p_val);
					return (FT)0.5 * TanH::fun(p_val) + ((FT)0.0535161 * val * val * val + (FT)0.398942 * val) * p_sech * p_sech + (FT)0.5;
				}

			private:
				constexpr static double pi() { return std::atan(1)*4; }
				constexpr static double sq2DivPi() { return std::sqrt(2/pi()); }
		};
	}
}

#endif // _NN_NER_ACTIVATION_GELU

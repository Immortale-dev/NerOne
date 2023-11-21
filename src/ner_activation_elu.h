#ifndef _NN_NER_ACTIVATION_ELU
#define _NN_NER_ACTIVATION_ELU

#include <algorithm>
#include <cmath>

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * Parametric Exponential Linear Unit activation function. For
		 * values less than 0, the result goes to -1 softly. Parameter
		 * decides the curve line for negative values. For values
		 * greater than 0, the result doesn't change.
		 *
		 * R should implement std::ratio class.
		 *
		 *                   /
		 *                 /
		 *  0 .........../
		 * -1 _________/
		 *             0
		 */
		template<typename R>
		class ELU {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return std::max(val, (FT)rat * (std::exp(val) - 1));
				}
				template<typename FT>
				inline static FT grad(FT val) {
					return val >= 0 ? 1 : (FT)rat * std::exp(val);
				}

			private:
				constexpr static double rat = (double)R::num / (double)R::den;
		};
	}
}

#endif // _NN_NER_ACTIVATION_ELU

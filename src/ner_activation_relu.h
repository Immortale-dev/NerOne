#ifndef _NN_NER_ACTIVATION_RELU
#define _NN_NER_ACTIVATION_RELU

#include <algorithm>
#include <ratio>

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * Parametric Reflicter activation function. For values less
		 * than 0, the result equals value * param. For values greater
		 * than 0, the result doesn't change.
		 *
		 * R should implement std::ratio class.
		 *
		 *                  /
		 *                /
		 *              /
		 * 0 _________/
		 *            0
		 */
		template<typename R = std::ratio<0,1>>
		class ReLU {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return std::max(val, val * rat);
				}
				template<typename FT>
				inline static FT grad(FT val) {
					return val >= 0 ? 1 : rat;
				}

			private:
				constexpr static long double rat = ((double)R::num/(double)R::den);
		};
	}
}

#endif // _NN_NER_ACTIVATION_RELU

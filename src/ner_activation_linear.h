#ifndef _NN_NER_ACTIVATION_LINEAR
#define _NN_NER_ACTIVATION_LINEAR

#include <cmath>

#include "ner_help.h"

namespace nerone {
	namespace activation {
		/**
		 * The linear function y=x.
		 */
		class Linear {
			public:
				template<typename FT>
				inline static FT fun(FT val) {
					return val;
				}
				template<typename FT>
				inline static FT grad(FT val) {
					return 1;
				}
		};
	}
}

#endif // _NN_NER_ACTIVATION_LINEAR

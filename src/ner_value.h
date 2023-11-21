#ifndef _NN_NER_VALUE
#define _NN_NER_VALUE

#include "ner_help.h"

namespace nerone {
	namespace value {
		/**
		 * Class extends basic Value class and additionally defines
		 * gradient functions that can be used in Gradient Descent back
		 * propagation algorithm.
		 */
		class Value {
			public:
				Value() = default;
				virtual ~Value() = default;
		};
	}
}

#endif // _NN_NER_VALUE

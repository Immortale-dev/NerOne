#ifndef _NN_NER_VALUE_F
#define _NN_NER_VALUE_F

#include "nerhelp.hpp"
#include "nervalue.hpp"

namespace nerone {
	namespace value {
		/**
		 * Abstract value class that defines floating point value.
		 */
		template<typename T>
		class FValue : public Value {
			public:
				using f_type = T;
				
				virtual T get() = 0;
				virtual void set(T value) = 0;
		};
	}
}

#endif // _NN_NER_VALUE_F

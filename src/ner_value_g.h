#ifndef _NN_NER_VALUE_G
#define _NN_NER_VALUE_G

#include "nerhelp.hpp"
#include "nerfvalue.hpp"

namespace nerone {
	namespace value {
		/**
		 * Abstract value class that defines gradient methods.
		 */
		template<typename T>
		class GValue : public FValue<T> {
			public:
				using f_type = T;
				
				virtual T get_grad() = 0;
				virtual void set_grad(T val) = 0;
		};
	}
}

#endif // _NN_NER_VALUE_G

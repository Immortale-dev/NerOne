#ifndef _NN_NER_VALUE_CU_BIAS
#define _NN_NER_VALUE_CU_BIAS

#include <stack>

#include "ner_help.h"
#include "ner_value_cu.h"

namespace nerone {
	namespace value {
		/**
		 * Cumulative value bias. Inplements the same 
		 */
		template<typename T>
		class CumulativeBias : public Cumulative<T> {
			public:
				using f_type = T;
				
				T get();
				void set(T val);
				T get_grad();
				void set_grad(T val);
				
				void pop();
				void clean();
				bool empty();
				
			private:
				T _val = 1.0;
		};
	}
}

#include "ner_value_cu_bias.hpp"

#endif // _NN_NER_VALUE_CU_BIAS

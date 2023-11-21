#ifndef _NN_NER_VALUE_CU
#define _NN_NER_VALUE_CU

#include <stack>

#include "ner_help.h"
#include "ner_value_g.h"

namespace nerone {
	namespace value {
		template<typename T>
		class Cumulative : public GValue<T> {
			public:
				using f_type = T;
				
				T get();
				void set(T val);
				T get_grad();
				void set_grad(T val);
				
				void pop();
				void clear();
				bool empty();
				
			private:
				bool _active = false;
				T _val;
				std::stack<T> _stack;
				T _grad;
		};
	}
}

#include "ner_value_cu.hpp"

#endif // _NN_NER_VALUE_CU

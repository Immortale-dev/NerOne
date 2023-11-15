#ifndef NN_CUVALUE
#define NN_CUVALUE

#include <stack>

#include "nerhelp.hpp"
#include "nergvalue.hpp"

namespace nerone {
	template<typename T>
	class CuValue : public GValue<T> {
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
	}
}

#include "nercuvalue.hpp"

#endif // NN_CUVALUE

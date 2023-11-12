#ifndef NN_GVALUE
#define NN_GVALUE

#include "nerhelp.hpp"
#include "nerfvalue.hpp"

namespace nerone {
	template<typename T>
	class GValue : public FValue<T> {
		public:
			virtual T get_grad() = 0;
			virtual void set_grad(T val) = 0;
	}
}

#endif // NN_GVALUE

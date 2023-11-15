#ifndef NN_FVALUE
#define NN_FVALUE

#include "nerhelp.hpp"
#include "nervalue.hpp"

namespace nerone {
	/**
	 * Abstract class that defines floating point value.
	 */
	template<typename T>
	class FValue : public Value {
		public:
			using f_type = T;
			
			virtual T get() = 0;
			virtual void set(T value) = 0;
	};
}

#endif // NN_FVALUE

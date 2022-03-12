#ifndef NN_ACTIVATIONS_RELU
#define NN_ACTIVATIONS_RELU

#include <algorithm>
#include <ratio>

#include "nerhelp.hpp"

namespace nerone {
	
	namespace activations {
		
		template<typename R = std::ratio<0,1>>
		class ReLU {
			public:
				inline static value_t fun(value_t val) {
					return std::max(val, val * rat);
				}
				inline static value_t grad(value_t val) {
					return val >= 0 ? 1 : rat;
				}
			
			private:
				constexpr static value_t rat = ((value_t)R::num/(value_t)R::den);
		};
	}
}

#endif // NN_ACTIVATIONS_RELU

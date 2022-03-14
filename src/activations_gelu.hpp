#ifndef NN_ACTIVATIONS_GELU
#define NN_ACTIVATIONS_GELU

#include <cmath>

#include "nerhelp.hpp"
#include "activations_tanh.hpp"

namespace nerone {
	
	namespace activations {
		
		class GELU {
			public:
				inline static value_t fun(value_t val) {
					return (value_t)0.5 * val * ((value_t)1 + TanH::fun(sq2DivPi() * (val + (value_t)0.044715 * val * val * val)));
				}
				inline static value_t grad(value_t val) {
					value_t p_val = (value_t)0.0356774 * val * val * val + (value_t)0.797885 * val;
					value_t p_sech = (value_t)1 / std::cosh(p_val);
					return (value_t)0.5 * TanH::fun(p_val) + ((value_t)0.0535161 * val * val * val + (value_t)0.398942 * val) * p_sech * p_sech + (value_t)0.5;
				}
			
			private:
				constexpr static value_t pi() { return std::atan(1)*4; }
				constexpr static value_t sq2DivPi() { return std::sqrt(2/pi()); }
		};
	}
}

#endif // NN_ACTIVATIONS_GELU

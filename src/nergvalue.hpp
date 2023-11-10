#ifndef NN_GVALUE
#define NN_GVALUE

#include "nerhelp.hpp"

namespace nerone {
	class GValue : public Value {
		public:
			GValue() = default;
			virtual ~GValue() = default;
			GValue(data_t val);
			
			virtual data_t get_grad();
			virtual void set_grad(data_t val);
			
		protected:
			data_t _gradient;
	}
}

#endif // NN_GVALUE

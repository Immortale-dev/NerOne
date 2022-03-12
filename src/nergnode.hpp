#ifndef NN_NERGNODE
#define NN_NERGNODE

#include "nerhelp.hpp"
#include "nernode.hpp"

namespace nerone {
	
	class NerGNode : public NerNode {
		public:
			NerGNode();
			NerGNode(value_t val);
			NerGNode(value_t val, act_fn_t fn, act_fn_t grad);
			void set_gradient_fn(act_fn_t fn);
			act_fn_t& get_gradient_fn();
			value_t get_gradient();
			
		private:
			act_fn_t gradient_fn;
	};
	
}

#endif // NN_NERGNODE

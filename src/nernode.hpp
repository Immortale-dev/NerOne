#ifndef NN_NERNODE
#define NN_NERNODE

#include "nerhelp.hpp"
#include "nersyn.hpp"

namespace nerone{

	class NerNode {
		
		public:
			NerNode();
			NerNode(value_t val);
			NerNode(value_t val, act_fn_t fn);
			virtual ~NerNode();
			value_t get_value();
			void set_value(value_t val);
			act_fn_t get_act_fn();
			void set_act_fn(act_fn_t fn);
			
		private:
			syn_list_t syns;
			value_t value;
			act_fn_t act_fn;
	};
}

#endif // NN_NERNODE

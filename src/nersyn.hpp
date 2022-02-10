#ifndef NN_NERSYN
#define NN_NERSYN

#include "nerhelp.hpp"

namespace nerone {
	class NerSyn {
		public:
			NerSyn();
			NerSyn(shared_node_t node, value_t weight);
			virtual ~NerSyn();
			value_t get_weight();
			void set_weight(value_t weight);
			shared_node_t get_node();
			void set_node(shared_node_t node);
			
		private:
			shared_node_t node;
			value_t weight;
	};
}

#endif

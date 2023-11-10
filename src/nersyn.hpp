#ifndef NN_NERSYN
#define NN_NERSYN

#include "nerhelp.hpp"

namespace nerone {
	/**
	 * It's not exactly a synops, but connection object containing a
	 * node of current layer with a node of previous layer and defines
	 * specific weight.
	 */
	class Syn {
		public:
			Syn();
			Syn(shared_node_t node, value_t weight);
			virtual ~Syn();
			value_t get_weight();
			void set_weight(value_t weight);
			shared_node_t get_value();
			void set_value(shared_node_t node);
			
		private:
			shared_node_t node;
			value_t weight;
	};
}

#endif

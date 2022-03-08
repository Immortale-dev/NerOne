#ifndef NN_NERLAYER
#define NN_NERLAYER

#include "nerhelp.hpp"

namespace nerone {
	class NerLayer {
		public:
			NerLayer();
			NerLayer(node_list_t nodes);
			virtual ~NerLayer();
			node_list_t& get_nodes();
			void set_nodes(node_list_t nodes);
			size_t size();
			shared_node_t& operator[](size_t ind);
			shared_node_t& get_bias();
			void set_bias(shared_node_t bias);
			
		private:
			node_list_t nodes;
			shared_node_t bias;
	};
}

#endif // NN_NERLAYER

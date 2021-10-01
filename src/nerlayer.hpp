#ifndef NN_NERLAYER
#define NN_NERLAYER

#include "nerhelp.hpp"

namespace nerone {
	class NerLayer {
		public:
			node_list_t& get_nodes();
			void set_nodes(node_list_t nodes);
			size_t size();
			operator[]();
			
		private:
			node_list_t nodes;
	}
}

#endif // NN_NERLAYER

#ifndef NN_NERCLUSTER
#define NN_NERCLUSTER

#include "nerhelp.hpp"

namespace nerone {
	class NerCluster {
		
		public:
			NerCluster();
			NerCluster(layer_list_t layers);
			virtual ~NerCluster();
			layer_list_t& get_layers();
			void set_layers(layer_list_t layers);
			
		private:
			layer_list_t layers;
	};
}

#endif // NN_NERCLUSTER

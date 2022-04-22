#ifndef NN_NERCLUSTER
#define NN_NERCLUSTER

#include "nerhelp.hpp"
#include "nerlayer.hpp"

namespace nerone {
	/**
	 * Instance of Cluster class contains list of layers connected in
	 * a single cluster to be processed by the propagation and back
	 * propagation algorithms.
	 */
	class Cluster {
		public:
			Cluster();
			Cluster(layer_list_t layers);
			virtual ~Cluster();
			layer_list_t& get_layers();
			void set_layers(layer_list_t layers);
			shared_layer_t& first_layer();
			shared_layer_t& last_layer();

		private:
			layer_list_t layers;
	};
}

#endif // NN_NERCLUSTER

#ifndef NN_NERHELP
#define NN_NERHELP

#include <memory>
#include <functional>
#include <vector>

namespace nerone {
	using value_t = double;
	using value_list_t = std::vector<value_t>;

	// Bakc decl
	class Node;
	class Syn;
	class Layer;
	class Cluster;

	using shared_node_t = std::shared_ptr<Node>;
	using shared_syn_t = std::shared_ptr<Syn>;
	using shared_layer_t = std::shared_ptr<Layer>;
	using shared_cluster_t = std::shared_ptr<Cluster>;

	using syn_list_t = std::vector<shared_syn_t>;
	using node_list_t = std::vector<shared_node_t>;
	using layer_list_t = std::vector<shared_layer_t>;

	using act_fn_t = std::function<value_t(value_t)>;
}

#endif // NN_NERHELP

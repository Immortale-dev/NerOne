#ifndef NN_NERHELP
#define NN_NERHELP

#include <memory>
#include <functional>
#include <vector>

namespace nerone {
	using value_t = long double;
	
	// Bakc decl
	class NerNode;
	class NerSyn;
	class NerLayer;
	
	using shared_node_t = std::shared_ptr<NerNode>;
	using shared_syn_t = std::shared_ptr<NerSyn>;
	using shared_layer_t = std::shared_ptr<NerLayer>;
	
	using syn_list_t = std::vector<shared_syn_t>;
	using node_list_t = std::vector<shared_node_t>;
	using layer_list_t = std::vector<shared_layer_t>;
	
	using act_fn_t = std::function<value_t(value_t)>;
}

#endif // NN_NERHELP

#ifndef NN_NERBOX
#define NN_NERBOX

#include <stdexcept>

#include "nerhelp.hpp"
#include "nercluster.hpp"

namespace nerone {
	
	template<typename M, typename T>
	class NerBox {
		// TODO
		// M - mutliplier class
		// T - teacher class
		
		public:
			NerBox();
			virtual ~NerBox();
			NerBox(shared_cluster_t cluster);
			
			shared_cluster_t get_cluster();
			void set_cluster(shared_cluster_t cluster);
			
			value_list_t question(value_list_t questions); // - processes all the vertices and returns the result
			void correct(value_list_t answers); // - back propagate all the vertices with current sums
			void teach(value_list_t questions, value_list_t answers); // question and correct
			
		protected:
			virtual void propagate(value_list_t&& questions);
			virtual void back_propagate(value_list_t&& answers);
		
		private:
			shared_cluster_t cluster;
			M mul;
			T tch;
	};
	
}

template<typename M, typename T>
nerone::NerBox<M,T>::NerBox() {
	// ctor
}

template<typename M, typename T>
nerone::NerBox<M,T>::~NerBox() {
	// dtor
}

template<typename M, typename T>
nerone::NerBox<M,T>::NerBox(shared_cluster_t cluster) : cluster(cluster) {
	// ctor
}

template<typename M, typename T>
nerone::shared_cluster_t nerone::NerBox<M,T>::get_cluster() {
	return cluster;
}

template<typename M, typename T>
void nerone::NerBox<M,T>::set_cluster(shared_cluster_t cluster) {
	this->cluster = cluster;
}

template<typename M, typename T>
nerone::value_list_t nerone::NerBox<M,T>::question(value_list_t questions) {
	if(!cluster) throw std::invalid_argument("No cluster set");
	layer_list_t& layers = cluster->get_layers();
	if(!layers.size()) throw std::range_error("No Layers defined");
	shared_layer_t first_layer = layers[0];
	
	if(first_layer->size() != questions.size()) {
		throw std::invalid_argument("Number of question data different from the number of nodes in the first layer");
	}
	
	// Propagate data
	propagate(std::move(questions));
	
	// Return the list
	shared_layer_t last_layer = layers[layers.size()-1];
	value_list_t ret(last_layer->size());
	int i=0;
	for(shared_node_t& node : last_layer->get_nodes()) {
		ret[i++] = node->get_value();
	}
	return ret;
}

template<typename M, typename T>
void nerone::NerBox<M,T>::correct(value_list_t answers) {
	if(!cluster) throw std::invalid_argument("No cluster set");
	layer_list_t& layers = cluster->get_layers();
	if(!layers.size()) throw std::range_error("No Layers defined");
	shared_layer_t last_layer = layers[layers.size()-1];
	
	if(last_layer->size() != answers.size()) {
		throw std::invalid_argument("Number of answer data different from the number of nodes in the last layer");
	}
	
	// Back propagate data
	back_propagate(std::move(answers));
}

template<typename M, typename T>
void nerone::NerBox<M,T>::teach(value_list_t questions, value_list_t answers) {
	question(questions);
	correct(answers);
}

template<typename M, typename T>
void nerone::NerBox<M,T>::propagate(value_list_t&& questions) {
	mul(cluster, std::move(questions));
}

template<typename M, typename T>
void nerone::NerBox<M,T>::back_propagate(value_list_t&& answers) {
	tch(cluster, std::move(answers));
}

#endif // NN_NERBOX

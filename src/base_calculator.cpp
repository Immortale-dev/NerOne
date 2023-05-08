#include "base_calculator.hpp"

nerone::BaseCalculator::Matrix nerone::BaseCalculator::matrix_create(value_list_t list) {
	return Matrix(std::vector<value_list_t>{list});
}

nerone::BaseCalculator::Matrix nerone::BaseCalculator::matrix_from_layer_syns(shared_layer_t prev_layer, shared_layer_t layer) {
	size_t syns_size = prev_layer->get_nodes()[0]->get_syns().size();
	vector<value_list_t> part_grad_mul_values(prev_layer->size(), value_list_t(syns_size,0));
	
	//shared_layer_t prev_layer = layers[i+1]; // means previous processed layer
	node_list_t& prev_nodes = prev_layer->get_nodes();
	for(size_t j=0;j<prev_nodes.size();j++){
		syn_list_t& syns = prev_nodes[j]->get_syns();
		for(size_t k=0;k<syns_size;k++){
			part_grad_mul_values[j][k] = syns[k]->get_weight();
		}
	}
	
	return Matrix(std::move(part_grad_mul_values));
}

void nerone::BaseCalculator::matrix_copy(Matrix& mat, value_list_t& list) {
	for(size_t j=0;j<list.size();j++){
		list[j] = mat.get(0, j);
	}
}

void nerone::BaseCalculator::update_layer_weights(shared_layer_t prev_layer, shared_layer_t layer, Matrix& mat, value_t rate) {
	node_list_t& prev_nodes = prev_layer->get_nodes();
	for(size_t j=0;j<prev_nodes.size();j++){
		syn_list_t& syns = prev_nodes[j]->get_syns();
		for(size_t k=0;k<layer->size();k++){
			// update syn's weights with respect of learning rate
			syns[k]->set_weight(syns[k]->get_weight() - mat.get(j,k) * rate);
		}
	}
}

void nerone::BaseCalculator::update_layer_biases(shared_layer_t prev_layer, shared_layer_t layer, Matrix& mat, value_t rate) {
	if(!prev_layer->get_bias()) return;
	node_list_t& prev_nodes = prev_layer->get_nodes();
	for(size_t j=0;j<prev_nodes.size();j++){
		syn_list_t& syns = prev_nodes[j]->get_syns();
		shared_syn_t bias_syn = syns[syns.size()-1];
		bias_syn->set_weight(bias_syn->get_weight() - mat.get(0,j) * rate);
	}
}

#ifndef NN_T_GRADIENT_DESCENT
#define NN_T_GRADIENT_DESCENT

#include "nerhelp.hpp"
#include "nersyn.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"
#include "nercluster.hpp"

namespace nerone {
	
	namespace teachers {
		
		template<typename N, typename L>
		class GradientDescent {
			public:
				void operator () (shared_cluster_t& cluster, value_list_t&& values);
				void set_learning_rate(long double rate);
				value_list_t get_errors(shared_cluster_t& cluster, value_list_t expected);
				
			private:
				L loss_f;
				long double learning_rate = 0.01;
		};
	}
}

template<typename N, typename L>
void nerone::teachers::GradientDescent<N, L>::operator () (shared_cluster_t& cluster, value_list_t&& values) {
	size_t values_size = values.size();
	
	value_list_t actual_vals(values_size);
	
	node_list_t last_layer_nodes = cluster->last_layer()->get_nodes();
	
	// get actual output values
	for(size_t i=0;i<values_size;i++){
		actual_vals[i] = last_layer_nodes[i]->get_output();
	}
	
	// calculate errors
	value_list_t loss_values(values_size);
	for(size_t i=0;i<values_size;i++){
		loss_values[i] = loss_f.fun(actual_vals[i], values[i]); // actual, expected
	}
	
	// store derivatives
	value_list_t gradients;
	
	layer_list_t& layers = cluster->get_layers();
	const size_t layers_size = layers.size();
	
	// Stores weight differences of the previously processed layer
	vector<value_list_t> prev_layer_diff_weights;
	
	// Process all weights of all layers
	for(size_t i=layers_size-1;i>=0;i--){ // since first layer is the input layer
		shared_layer_t layer = layers[i];
		node_list_t& nodes = layer->get_nodes();
		bool is_output_layer = i == layers_size-1;
		bool is_input_layer = i == 0;
		
		if(is_output_layer){
			gradients.resize(layer->size());
			for(size_t j=0;j<layer->size();j++){
				// partial chain rule: dE/dO * dO/dOz
				// * E = error
				// * O = output layer's node output
				// * Oz = output layer's node value
				gradients[j] = loss_f.grad(actual_vals[j], values[j]) * std::static_pointer_cast<NerGNode>(nodes[j])->get_gradient_fn()(nodes[j]->get_output());
			}
		} else {
			// partial chain rule derivatives: dE/dHz
			// * E = error
			// * Hz = prev processed layer's node value
			vector<value_list_t> prev_chain_grad_values = {gradients}; 
			vector<value_list_t> part_grad_mul_values(gradients.size(), value_list_t(nodes.size(),0));
			
			shared_layer_t prev_layer = layers[i+1]; // means previous processed layer
			node_list_t& prev_nodes = prev_layer->get_nodes();
			for(size_t j=0;j<prev_nodes.size();j++){
				syn_list_t& syns = prev_nodes[j]->get_syns();
				for(size_t k=0;k<nodes.size();k++){
					part_grad_mul_values[j][k] = syns[k]->get_weight();
				}
			}
			
			// weights taken here, we can update previous layer's node weights
			for(size_t j=0;j<prev_nodes.size();j++){
				syn_list_t& syns = prev_nodes[j]->get_syns();
				for(size_t k=0;k<nodes.size();k++){
					// update syn's weights with respect of learning rate
					syns[k]->set_weight(syns[k]->get_weight() - prev_layer_diff_weights[j][k] * learning_rate);
				}
				
				// Update bias
				if(prev_layer->get_bias()){
					shared_syn_t bias_syn = syns[syns.size()-1];
					bias_syn->set_weight(bias_syn->get_weight() - gradients[j] * learning_rate);
				}
			}
			
			// No syns go to input layer
			if(is_input_layer){
				return;
			}
			
			Matrix<value_t> prev_chain_grad_mat(std::move(prev_chain_grad_values));
			Matrix<value_t> part_grad_mul_mat(std::move(part_grad_mul_values));
			
			Matrix<value_t> part_grad_mat = prev_chain_grad_mat * part_grad_mul_mat;
			
			gradients.resize(nodes.size());
			for(size_t j=0;j<gradients.size();j++){
				// partial chain rule derivatives: dE/dHz
				// * E = error
				// * Hz = current layer's node value
				gradients[j] = part_grad_mat.get(0,j) * std::static_pointer_cast<NerGNode>(nodes[j])->get_gradient_fn()(nodes[j]->get_output());
			}
		}
		
		// fill weights differences
		prev_layer_diff_weights.resize(nodes.size());
		for(size_t j=0;j<nodes.size();j++){
			shared_node_t node = nodes[j];
			syn_list_t& syns = node->get_syns();
			
			size_t syns_size = layers[i-1]->get_nodes().size();
			
			value_list_t node_weights(syns_size);
			
			for(size_t k=0;k<syns_size;k++){
				// weight differences: dE/dW
				// * E - error
				// * W - syn's weight
				node_weights[k] = gradients[j] * syns[k]->get_node()->get_output();
			}
			prev_layer_diff_weights[j] = std::move(node_weights);
		}
	}
}

template<typename N, typename L>
void nerone::teachers::GradientDescent<N, L>::set_learning_rate(long double rate) {
	this->learning_rate = rate;
}

template<typename N, typename L>
nerone::value_list_t nerone::teachers::GradientDescent<N, L>::get_errors(shared_cluster_t& cluster, value_list_t expected) {
	node_list_t& nodes = cluster->last_layer()->get_nodes();
	value_list_t errors(expected.size());
	for(size_t i=0;i<expected.size();i++){
		errors[i] = loss_f.fun(nodes[i]->get_output(), expected[i]);
	}
	return errors;
}

#endif // NN_T_GRADIENT_DESCENT

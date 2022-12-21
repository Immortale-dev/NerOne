#ifndef NN_T_GRADIENT_DESCENT
#define NN_T_GRADIENT_DESCENT

#include "nerhelp.hpp"
#include "nersyn.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"
#include "nercluster.hpp"
#include "base_calculator.hpp"

namespace nerone {
	namespace teachers {
		/**
		 * Gradient Descent back propagation algorithm. Accepts template
		 * parameter N representing Node class that needs to be used,
		 * and needs to implement `get_gradient()` public function that
		 * returns gradient of current node value.
		 * Accepts template parameter L representing loss function
		 * class.
		 * Accepts template parameter O that allow to provide
		 * multiplication optimisations. O class should implement
		 * BaseCalculator interface.
		 */
		template<typename N, typename L, typename O = BaseCalculator>
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

template<typename N, typename L, typename O>
void nerone::teachers::GradientDescent<N, L, O>::operator () (shared_cluster_t& cluster, value_list_t&& values) {
	node_list_t last_layer_nodes = cluster->last_layer()->get_nodes();

	// store derivatives
	value_list_t gradients;

	layer_list_t& layers = cluster->get_layers();
	const size_t layers_size = layers.size();

	// Stores weight differences of the previously processed layer
	typename O::Matrix prev_layer_diff_weights;

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
				gradients[j] = loss_f.grad(last_layer_nodes[j]->get_output(), values[j]) * std::static_pointer_cast<N>(nodes[j])->get_gradient();
			}
		} else {
			// partial chain rule derivatives: dE/dHz
			// * E = error
			// * Hz = prev processed layer's node value
			typename O::Matrix m1 = O::matrix_create(gradients);

			if (!is_input_layer) {
				// create syns matrix from previous processed layer
				typename O::Matrix m2 = O::matrix_from_layer_syns(layers[i+1], layers[i], true);

				// partial chain rule derivatives: dE/dHo
				// * E = error
				// * Hz = current layer's node output
				typename O::Matrix m_res = m1 * m2;

				// Copy data from matrix back to vector
				gradients.resize(nodes.size()+1);
				O::matrix_copy(m_res, gradients);

				// Since the m2 matrix contains also biases that shoudn't be included
				// to the gradients list, just pop the last element out.
				gradients.pop_back();

				for(size_t j=0;j<gradients.size();j++){
					// partial chain rule derivatives: dE/dHz
					// * E = error
					// * Hz = current layer's node value
					gradients[j] *= std::static_pointer_cast<N>(nodes[j])->get_gradient();
				}
			}

			// weights are taken here and multiplication is done, we can update previous layer's node weights
			O::update_layer_weights(layers[i+1], layers[i], prev_layer_diff_weights, learning_rate);

			// Biases updated with respect of gradients
			O::update_layer_biases(layers[i+1], layers[i], m1, learning_rate);
		}

		// No syns go to input layer
		if(is_input_layer){
			return;
		}

		// Next processed layer
		shared_layer_t next_layer = layers[i-1];
		size_t syns_size = next_layer->get_nodes().size();
		value_list_t next_layer_node_outputs(syns_size);
		node_list_t& next_layer_nodes = next_layer->get_nodes();
		for(size_t j=0;j<syns_size;j++){
			next_layer_node_outputs[j] = next_layer_nodes[j]->get_output();
		}

		// partial chain rule derivatives: dE/dHz
		// * E = error
		// * Hz = current layer's node value
		typename O::Matrix m1 = O::matrix_create(gradients);

		// Node outputs
		typename O::Matrix m2 = O::matrix_create(next_layer_node_outputs);

		// Transpose so the matrix is Nx1 [[x],[x],[x],[x],[x],...]
		m1.transpose();

		// weight differences: dE/dW
		// * E - error
		// * W - syn's weight
		prev_layer_diff_weights = m1 * m2;
	}
}

template<typename N, typename L, typename O>
void nerone::teachers::GradientDescent<N, L, O>::set_learning_rate(long double rate) {
	this->learning_rate = rate;
}

template<typename N, typename L, typename O>
nerone::value_list_t nerone::teachers::GradientDescent<N, L, O>::get_errors(shared_cluster_t& cluster, value_list_t expected) {
	node_list_t& nodes = cluster->last_layer()->get_nodes();
	value_list_t errors(expected.size());
	for(size_t i=0;i<expected.size();i++){
		errors[i] = loss_f.fun(nodes[i]->get_output(), expected[i]);
	}
	return errors;
}

#endif // NN_T_GRADIENT_DESCENT

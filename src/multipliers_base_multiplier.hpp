#ifndef NN_BASE_MULTIPLIER
#define NN_BASE_MULTIPLIER

#include "nerhelp.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"
#include "nercluster.hpp"
#include "base_calculator.hpp"

namespace nerone {
	namespace multipliers {
		/**
		 * Class implements neuron network propagation algorithm.
		 * Accepts template parameter O that allow to provide
		 * multiplication optimisations. O class should implement
		 * BaseCalculator interface.
		 */
		template<typename O = BaseCalculator>
		class BaseMultiplier {
			public:
				void operator () (shared_cluster_t& cluster, value_list_t&& values);
		};
	}
}

template<typename O>
void nerone::multipliers::BaseMultiplier<O>::operator () (shared_cluster_t& cluster, value_list_t&& values) {
	layer_list_t& layers = cluster->get_layers();

	value_list_t vals = std::move(values);

	size_t ind=1;
	do{
		node_list_t& prev_nodes = layers[ind-1]->get_nodes();
		for(size_t i=0;i<vals.size();i++){
			prev_nodes[i]->set_value(vals[i]);
			vals[i] = prev_nodes[i]->get_output();
		}

		if(ind >= layers.size()) break;

		// Add bias to the list of values
		if(layers[ind-1]->get_bias()){
			vals.push_back(layers[ind-1]->get_bias()->get_value());
		}

		typename O::Matrix b_vals = O::matrix_create(vals);

		typename O::Matrix m_vals = O::matrix_from_layer_syns(layers[ind], layers[ind-1]);

		// Transpose for correct matrix multiplication
		b_vals.transpose();

		// Result of matrix multiplication is Nx1 matrix [[x],[x],[x],[x],[x],[x],...]
		typename O::Matrix res = m_vals * b_vals;

		// Transpose so the result is 1xN matrix [[x,x,x,x,x,x,x,x,...]]
		// Note, it's better for performance to transpose 1xN matrix twice than NxN matrix once.
		res.transpose();

		vals.resize(res.get_cols());
		O::matrix_copy(res, vals);
	}while(ind++<layers.size());
}

#endif // NN_BASE_MULTIPLIER

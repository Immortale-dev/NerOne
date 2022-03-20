#ifndef NN_BASE_MULTIPLIER
#define NN_BASE_MULTIPLIER

#include "nerhelp.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"
#include "nercluster.hpp"
#include "matrix.hpp"
#include "base_calculator.hpp"

namespace nerone {
	
	namespace multipliers {
	
		template<typename O = BaseCalculator>
		class BaseMultiplier {
			public:
				void operator () (shared_cluster_t& cluster, value_list_t&& values);
			
			private:
				using v_mat_mul_t = typename O::vector_matrix_multiplication<value_t>;
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
		
		typename O::Matrix m_vals = O::matrix_from_layer_syns(layers[ind], layers[ind-1], true);
		
		// Transpose for correct matrix multiplication
		m_vals.transpose();

		// Result of matrix multiplication should be [[x,x,x,x,x,x,...]]
		typename O::Matrix res = b_vals * m_vals;

		vals.resize(res.get_cols());
		O::matrix_copy(res, vals, 0);
	}while(ind++<layers.size());
}

#endif // NN_BASE_MULTIPLIER

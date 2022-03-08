#include "base_multiplier.hpp"

#include <iostream>

void nerone::multipliers::BaseMultiplier::operator () (shared_cluster_t& cluster, value_list_t&& values) {
	layer_list_t& layers = cluster->get_layers();
	
	value_list_t vals = std::move(values);
	
	size_t ind=1;
	do{
		node_list_t& nodes = layers[ind]->get_nodes();
		
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
		
		Matrix<value_t> b_vals({vals});
		
		vector<vector<value_t>> m_t_vals(nodes.size());

		int j=0;
		for(auto& node : nodes) {
			syn_list_t& syns = node->get_syns();
			vector<value_t> l_vals(syns.size());
			
			int i=0;
			for(auto& syn : syns) {
				l_vals[i++] = syn->get_weight();
			}
			
			m_t_vals[j++] = std::move(l_vals);
		}

		Matrix<value_t> m_vals(std::move(m_t_vals));
		
		// Transpose for correct matrix multiplication
		m_vals.transpose();

		// Result of matrix multiplication should be [[x,x,x,x,x,x,...]]
		Matrix<value_t> res = b_vals * m_vals;

		vals.resize(res.get_cols());
		for(size_t i=0;i<res.get_cols();i++){
			vals[i] = res.get(0,i);
		}
	}while(ind++<layers.size());
}

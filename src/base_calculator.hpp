#ifndef NN_BASE_OPTIMIZER
#define NN_BASE_OPTIMIZER

#include <vector>

#include "nerhelp.hpp"
#include "matrix.hpp"
#include "nersyn.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"

namespace nerone {
	struct BaseCalculator {
		template<typename T>
		struct vector_matrix_multiplication {
			std::vector<std::vector<T>> operator () (std::vector<std::vector<T>>& m1, std::vector<std::vector<T>>& m2);
		};
		
		using Matrix = nerone::Matrix<value_t, vector_matrix_multiplication<value_t>>;
		
		static Matrix matrix_create(value_list_t list);
		static Matrix matrix_from_layer_syns(shared_layer_t prev_layer, shared_layer_t layer, bool with_biases = false);
		static void matrix_copy(Matrix& mat, value_list_t& list, size_t row);
		static void update_layer_weights(shared_layer_t prev_layer, shared_layer_t layer, Matrix& mat, value_t rate);
		static void update_layer_biases(shared_layer_t prev_layer, shared_layer_t layer, Matrix& mat, value_t rate);
	};
}

template<typename T>
std::vector<std::vector<T>> nerone::BaseCalculator::vector_matrix_multiplication<T>::operator () (std::vector<std::vector<T>>& m1, std::vector<std::vector<T>>& m2) {
	const size_t r = m1.size();
	const size_t c = m2[0].size();
	
	std::vector<std::vector<T>> res(r, std::vector<T>(c, 0));
	
	for(size_t i=0;i<r;i++){
		for(size_t j=0;j<c;j++){
			for(size_t k=0;k<m1[i].size();k++) {
				res[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
	
	return res;
}

nerone::BaseCalculator::Matrix nerone::BaseCalculator::matrix_create(value_list_t list) {
	return Matrix(std::vector<value_list_t>{list});
}

nerone::BaseCalculator::Matrix nerone::BaseCalculator::matrix_from_layer_syns(shared_layer_t prev_layer, shared_layer_t layer, bool with_biases) {
	size_t syns_size = with_biases ? prev_layer->get_nodes()[0]->get_syns().size() : layer->size();
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

void nerone::BaseCalculator::matrix_copy(Matrix& mat, value_list_t& list, size_t row) {
	for(size_t j=0;j<list.size();j++){
		list[j] = mat.get(row, j);
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

#endif // NN_BASE_OPTIMIZER

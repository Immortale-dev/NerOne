#ifndef NN_BASE_OPTIMIZER
#define NN_BASE_OPTIMIZER

#include <vector>

namespace nerone {
	struct BaseCalculator {
		template<typename T>
		struct vector_matrix_multiplication {
			std::vector<std::vector<T>> operator () (std::vector<std::vector<T>>& m1, std::vector<std::vector<T>>& m2);
		};
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

#endif // NN_BASE_OPTIMIZER
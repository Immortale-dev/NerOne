#ifndef NN_MATRIX
#define NN_MATRIX

#define NN_MATRIX_TEMPLATE template<typename T, typename M>

#include <functional>
#include <stdexcept>
#include <vector>

#include "base_calculator.hpp"

namespace nerone {
	
	template<typename T>
	using vector = std::vector<T>;
	
	template<typename T>
	using mat_vec_t = vector<vector<T>>;
	
	template<typename T, typename M = nerone::BaseCalculator::vector_matrix_multiplication<T>>
	class Matrix {
		public:
			Matrix();
			Matrix(size_t rows, size_t cols);
			Matrix(vector<vector<T>>&& vec);
			virtual ~Matrix();
			void set(size_t r, size_t c, T val);
			T get(size_t r, size_t c);
			const size_t get_rows();
			const size_t get_cols();
			Matrix<T,M> operator * (Matrix<T,M>& mul);
			void transpose();
			mat_vec_t<T>& get_vector();
		private:
			size_t rows;
			size_t cols;
			vector<vector<T>> mat;
			M multiply;
	};
	
}

NN_MATRIX_TEMPLATE
nerone::Matrix<T,M>::Matrix() : rows(0), cols(0) {}

NN_MATRIX_TEMPLATE
nerone::Matrix<T,M>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), mat(rows, vector<T>(cols)) {}

NN_MATRIX_TEMPLATE
nerone::Matrix<T,M>::Matrix(vector<vector<T>>&& vec) : rows(vec.size()), cols(vec[0].size()), mat(std::move(vec)) {}

NN_MATRIX_TEMPLATE
nerone::Matrix<T,M>::~Matrix() {};

NN_MATRIX_TEMPLATE
void nerone::Matrix<T,M>::set(size_t r, size_t c, T val) {
	mat[r][c] = val;
}

NN_MATRIX_TEMPLATE
T nerone::Matrix<T,M>::get(size_t r, size_t c) {
	return mat[r][c];
}

NN_MATRIX_TEMPLATE
const size_t nerone::Matrix<T,M>::get_rows() {
	return rows;
}

NN_MATRIX_TEMPLATE
const size_t nerone::Matrix<T,M>::get_cols() {
	return cols;
}

NN_MATRIX_TEMPLATE
nerone::Matrix<T,M> nerone::Matrix<T,M>::operator * (Matrix<T,M>& mul) {
	if(this->get_cols() != mul.get_rows()) {
		throw std::logic_error("number of cols of the first Matrix != number of rows of the second Matrix");
	}
	return Matrix<T>(multiply(this->mat, mul.mat));
}

NN_MATRIX_TEMPLATE
void nerone::Matrix<T,M>::transpose() {
	mat_vec_t<T> res(cols, vector<T>(rows));
	
	for(size_t i=0;i<rows;i++){
		for(size_t j=0;j<cols;j++){
			res[j][i] = mat[i][j];
		}
	}
	
	mat = res;
	std::swap(rows,cols);
}

NN_MATRIX_TEMPLATE
nerone::mat_vec_t<T>& nerone::Matrix<T,M>::get_vector() {
	return mat;
}


#endif // NN_MATRIX

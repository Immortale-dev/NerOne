#include "mean_square_error_loss.hpp"

nerone::value_t nerone::loss::MeanSquareError::fun(value_t actual, value_t expected) {
	return (value_t)0.5 * (actual - expected) * (actual - expected);
}

nerone::value_t nerone::loss::MeanSquareError::grad(value_t actual, value_t expected) {
	return actual - expected;
}

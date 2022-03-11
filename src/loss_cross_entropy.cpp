#include "loss_cross_entropy.hpp"

nerone::value_t nerone::loss::CrossEntropy::fun(value_t actual, value_t expected) {
	return -(expected * std::log2(actual) + ((value_t)1 - expected) * std::log2((value_t)1 - actual));
}

nerone::value_t nerone::loss::CrossEntropy::grad(value_t actual, value_t expected) {
	return (actual - expected) / (actual * ((value_t)1 - actual));
}

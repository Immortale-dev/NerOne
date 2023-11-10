#include "nergvalue.hpp"

nerone::GValue::GValue(data_t val) : Value(val) {}

nerone::data_t nerone::GValue::get_grad() {
	return _gradient;
}

void nerone::GValue::set_grad(data_t val) {
	_gradient = val;
}

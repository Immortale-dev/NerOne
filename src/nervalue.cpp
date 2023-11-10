#include "nervalue.hpp"

nerone::Value::Value(data_t val) : val(val) {}

nerone::data_t nerone::Value::get() {
	return val;
}

void nerone::Value::set(data_t val) {
	this->val = val;
}

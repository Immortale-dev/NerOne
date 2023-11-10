#include "nerinputvalue.hpp"

nerone::InputValue::InputValue(data_t val) : Value(val) {}

nerone::syn_list_t& nerone::InputValue::get_syns() {
	return _syns;
}

void nerone::InputValue::set_syns(syn_list_t list) {
	_syns = list;
}

nerone::data_t nerone::InputValue::get_bias() {
	return _bias;
}

void nerone::InputValue::set_bias(data_t val) {
	_bias = val;
}

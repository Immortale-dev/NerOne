#include "nervalue.hpp"

nerone::Value::Value() {}

nerone::Value::Value(value_t val) : val(val) {}

nerone::Value::~Value() {}

nerone::syn_list_t& nerone::Node::get_syns() {
	return syns;
}

void nerone::Node::set_syns(syn_list_t syns) {
	this->syns = syns;
}

nerone::value_t nerone::Value::get() {
	return val;
}

void nerone::Value::set(value_t val) {
	this->val = val;
}

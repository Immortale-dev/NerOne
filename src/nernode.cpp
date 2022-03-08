#include "nernode.hpp"

nerone::NerNode::NerNode() {}

nerone::NerNode::NerNode(value_t val) : value(val) {}

nerone::NerNode::NerNode(value_t val, act_fn_t fn) : value(val), act_fn(fn) {}

nerone::NerNode::~NerNode() {}

nerone::value_t nerone::NerNode::get_value() {
	return value;
}

void nerone::NerNode::set_value(value_t val) {
	value = val;
}

nerone::act_fn_t& nerone::NerNode::get_act_fn() {
	return act_fn;
}

void nerone::NerNode::set_act_fn(act_fn_t fn) {
	act_fn = fn;
}

nerone::syn_list_t& nerone::NerNode::get_syns() {
	return syns;
}

void nerone::NerNode::set_syns(syn_list_t syns) {
	this->syns = syns;
}

nerone::value_t nerone::NerNode::get_output() {
	return act_fn ? act_fn(value) : value;
}

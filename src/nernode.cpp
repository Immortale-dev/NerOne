#include "nernode.hpp"

nerone::Node::Node() {}

nerone::Node::Node(value_t val) : value(val) {}

nerone::Node::Node(value_t val, act_fn_t fn) : value(val), act_fn(fn) {}

nerone::Node::~Node() {}

nerone::value_t nerone::Node::get_value() {
	return value;
}

void nerone::Node::set_value(value_t val) {
	value = val;
}

nerone::act_fn_t& nerone::Node::get_act_fn() {
	return act_fn;
}

void nerone::Node::set_act_fn(act_fn_t fn) {
	act_fn = fn;
}

nerone::syn_list_t& nerone::Node::get_syns() {
	return syns;
}

void nerone::Node::set_syns(syn_list_t syns) {
	this->syns = syns;
}

nerone::value_t nerone::Node::get_output() {
	return act_fn ? act_fn(value) : value;
}

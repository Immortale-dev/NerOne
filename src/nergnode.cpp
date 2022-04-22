#include "nergnode.hpp"

nerone::GNode::GNode() : Node() {}

nerone::GNode::GNode(value_t val) : Node(val) {}

nerone::GNode::GNode(value_t val, act_fn_t act, act_fn_t grad) : Node(val, act), gradient_fn(grad) {}

void nerone::GNode::set_gradient_fn(act_fn_t fn) {
	gradient_fn = fn;
}

nerone::act_fn_t& nerone::GNode::get_gradient_fn() {
	return gradient_fn;
}

nerone::value_t nerone::GNode::get_gradient() {
	return gradient_fn ? gradient_fn(value) : value;
}

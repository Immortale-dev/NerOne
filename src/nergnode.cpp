#include "nergnode.hpp"

nerone::NerGNode::NerGNode() : NerNode() {}

nerone::NerGNode::NerGNode(value_t val) : NerNode(val) {}

nerone::NerGNode::NerGNode(value_t val, act_fn_t act, act_fn_t grad) : NerNode(val, act), gradient_fn(grad) {}

void nerone::NerGNode::set_gradient_fn(act_fn_t fn) {
	gradient_fn = fn;
}

nerone::act_fn_t& nerone::NerGNode::get_gradient_fn() {
	return gradient_fn;
}

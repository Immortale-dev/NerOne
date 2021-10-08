#include "nersyn.hpp"

nerone::NerSyn::NerSyn() {}

nerone::NerSyn::NerSyn(shared_node_t node, value_t weight) : node(node), weight(weight) {}

nerone::NerSyn::~NerSyn() {}

nerone::value_t nerone::NerSyn::get_weight() {
	return weight;
}

void nerone::NerSyn::set_weight(value_t weight) {
	this->weight = weight;
}

nerone::shared_node_t nerone::NerSyn::get_node() {
	return node;
}

void nerone::NerSyn::set_node(shared_node_t node) {
	this->node = node;
}

#include "nersyn.hpp"

nerone::Syn::Syn() {}

nerone::Syn::Syn(shared_node_t node, value_t weight) : node(node), weight(weight) {}

nerone::Syn::~Syn() {}

nerone::value_t nerone::Syn::get_weight() {
	return weight;
}

void nerone::Syn::set_weight(value_t weight) {
	this->weight = weight;
}

nerone::shared_node_t nerone::Syn::get_node() {
	return node;
}

void nerone::Syn::set_node(shared_node_t node) {
	this->node = node;
}

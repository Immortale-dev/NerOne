#include "nersyn.hpp"

nerone::Syn::Syn() {}

nerone::Syn::Syn(shared_value_t node, data_t weight) : node(node), weight(weight) {}

nerone::Syn::~Syn() {}

nerone::data_t nerone::Syn::get_weight() {
	return weight;
}

void nerone::Syn::set_weight(data_t weight) {
	this->weight = weight;
}

nerone::shared_value_t nerone::Syn::get_value() {
	return node;
}

void nerone::Syn::set_value(shared_value_t node) {
	this->node = node;
}

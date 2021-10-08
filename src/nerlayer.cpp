#include "nerlayer.hpp"

nerone::NerLayer::NerLayer(){}

nerone::NerLayer::NerLayer(node_list_t nodes) : nodes(nodes) {}

nerone::NerLayer::~NerLayer() {}

nerone::node_list_t& nerone::NerLayer::get_nodes() {
	return nodes;
}

void nerone::NerLayer::set_nodes(node_list_t nodes) {
	this->nodes = nodes;
}

size_t nerone::NerLayer::size() {
	return nodes.size();
}

nerone::shared_node_t& nerone::NerLayer::operator[](size_t ind) {
	return nodes[ind];
}

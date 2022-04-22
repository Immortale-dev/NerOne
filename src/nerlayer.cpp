#include "nerlayer.hpp"

nerone::Layer::Layer(){}

nerone::Layer::Layer(node_list_t nodes) : nodes(nodes) {}

nerone::Layer::~Layer() {}

nerone::node_list_t& nerone::Layer::get_nodes() {
	return nodes;
}

void nerone::Layer::set_nodes(node_list_t nodes) {
	this->nodes = nodes;
}

size_t nerone::Layer::size() {
	return nodes.size();
}

nerone::shared_node_t& nerone::Layer::operator[](size_t ind) {
	return nodes[ind];
}

nerone::shared_node_t& nerone::Layer::get_bias() {
	return bias;
}

void nerone::Layer::set_bias(shared_node_t bias) {
	this->bias = bias;
}

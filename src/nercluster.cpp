#include "nercluster.hpp"

nerone::NerCluster::NerCluster() {}

nerone::NerCluster::NerCluster(layer_list_t layers) : layers(layers) {}

nerone::NerCluster::~NerCluster() {}

nerone::layer_list_t& nerone::NerCluster::get_layers() {
	return layers;
}

void nerone::NerCluster::set_layers(layer_list_t layers) {
	this->layers = layers;
}

nerone::shared_layer_t& nerone::NerCluster::first_layer() {
	return this->layers[0];
}

nerone::shared_layer_t& nerone::NerCluster::last_layer() {
	return this->layers[this->layers.size()-1];
}

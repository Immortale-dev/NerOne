#include "nercluster.hpp"

nerone::NerCluster::NerCluster() {}

nerone::NerCluster::NerCluster(layer_list_t layers) : layers(layers) {}

nerone::NerCluster::~NerCluster() {}

nerone::layer_list_t nerone::NerCluster::get_layers() {
	return layers;
}

void nerone::NerCluster::set_layers(layer_list_t layers) {
	this->layers = layers;
}

#include "nercluster.hpp"

nerone::Cluster::Cluster() {}

nerone::Cluster::Cluster(layer_list_t layers) : layers(layers) {}

nerone::Cluster::~Cluster() {}

nerone::layer_list_t& nerone::Cluster::get_layers() {
	return layers;
}

void nerone::Cluster::set_layers(layer_list_t layers) {
	this->layers = layers;
}

nerone::shared_layer_t& nerone::Cluster::first_layer() {
	return this->layers[0];
}

nerone::shared_layer_t& nerone::Cluster::last_layer() {
	return this->layers[this->layers.size()-1];
}

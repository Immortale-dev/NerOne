#include "nerbox.hpp"

nerone::NerBox::NerBox() {
	// ctor
}

nerone::NerBox::~NerBox() {
	// dtor
}

nerone::NerBox::NerBox(ner_cluster_t cluster) : cluster(cluster) {
	// ctor
}

nerone::ner_cluster_t nerone::NerBox::get_cluster() {
	return cluster;
}

void nerone::NerBox::set_cluster(ner_cluster_t cluster) {
	this->cluster = cluster;
}

nerone::values_t nerone::NerBox::question(values_t questions) {
	// todo
}

void nerone::NerBox::correct(values_t answers) {
	// todo
}

void nerone::NerBox::teach(values_t questions, values_t answers) {
	// todo
}

void nerone::NerBox::propagate() {
	// todo
}

void nerone::NerBox::back_propagate() {
	// todo
}

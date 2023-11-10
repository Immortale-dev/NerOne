#include "nerconvactcell.hpp"

nerone::ConvActCell::ConvActCell() : _conv(nullptr), _act(nullptr) {}

nerone::ConvActCell::ConvActCell(shared_cell_t conv, shared_cell_t act) : _conv(conv), _act(act) {}

nerone::shared_cell_t nerone::ConvActCell::get_conv() {
	return _conv;
}

nerone::shared_cell_t nerone::ConvActCell::get_act() {
	return _act;
}

void nerone::ConvActCell::set_conv(shared_cell_t cell) {
	_conv = cell;
}

void nerone::ConvActCell::set_act(shared_cell_t cell) {
	_act = cell;
}

nerone::value_list_t& nerone::ConvActCell::inputs() {
	return _conv.inputs();
}

nerone::value_list_t& nerone::ConvActCell::outputs() {
	return _act.outputs();
}

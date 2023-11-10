#include "nerconvcell.hpp"

nerone::ConvCell::ConvCell(shared_value_t val) : _value(val), _value_list(1, _value) {}

nerone::ConvCell::ConvCell() : _value(nullptr), _value_list(1, _value) {}

nerone::shared_value_t& get_value() {
	return _value;
}

void nerone::ConvCell::set_value(shared_value_t value) {
	_value = value;
	_value_list[0] = value;
}

nerone::value_t nerone::ConvCell::get_bias() {
	return _bias;
}

void nerone::ConvCell::set_bias(value_t bias) {
	_bias = value;
}

nerone::value_list_t& nerone::ConvCell::inputs() {
	return _value_list;
}

nerone::value_list_t& nerone::ConvCell::outputs() {
	return _value_list;
}

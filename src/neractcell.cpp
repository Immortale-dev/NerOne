#include "neractcell.hpp"

nerone::ActCell::ActCell() : _value(nullptr), _value_list(1, _value) {}

nerone::ActCell::ActCell(shared_value_t val) : _value(val), _value_list(1, _value) {}

nerone::ActCell::ActCell(shared_value_t val, act_fn_t act, act_fn_t grad) : _value(val), _value_list(1, _value), _act(act), _grad(grad) {}

nerone::shared_value_t& nerone::ActCell::get_value() {
	return _value;
}

void nerone::ActCell::set_value(shared_value_t value) {
	_value = value;
}

nerone::act_fn_t nerone::ActCell::get_act() {
	return _act;
}

nerone::act_fn_t nerone::ActCell::get_grad() {
	return _grad;
}

void nerone::ActCell::set_act(act_fn_t act) {
	_act = act;
}

void nerone::ActCell::set_grad(act_fn_t grad) {
	_grad = grad;
}

nerone::value_list_t& nerone::ActCell::inputs() {
	return _value_list;
}

nerone::value_list_t& nerone::ActCell::outputs() {
	return _value_list;
}
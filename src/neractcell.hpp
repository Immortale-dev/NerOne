template<typename VT>
nerone::ActCell::ActCell() : ActCell(std::make_shared<VT>(), std::make_shared<VT>(), nullptr, nullptr) {}

template<typename VT>
nerone::ActCell::ActCell(shared_value_t input, shared_value_t output) : ActCell(input, output, nullptr, nullptr) {}

template<typename VT>
nerone::ActCell::ActCell(act_fn_t act, act_fn_t grad) : ActCell(std::make_shared<VT>(), std::make_shared<VT>(), act, grad) {}

template<typename VT>
nerone::ActCell::ActCell(shared_value_t input, act_fn_t act, act_fn_t grad) : ActCell(input, std::make_shared<VT>(), nullptr, nullptr) {}

template<typename VT>
nerone::ActCell::ActCell(shared_value_t input, shared_value_t output, act_fn_t act, act_fn_t grad) :
	_input_value(input),
	_output_value(output),
	_input_value_list(1, _input_value),
	_output_value_list(1, _output_value),
	_act(act),
	_grad(grad)
{}

template<typename VT>
nerone::act_fn_t nerone::ActCell::get_act_fn() {
	return _act;
}

template<typename VT>
nerone::act_fn_t nerone::ActCell::get_grad_fn() {
	return _grad;
}

template<typename VT>
void nerone::ActCell::set_act_fn(act_fn_t fn) {
	_act = fn;
}

template<typename VT>
void nerone::ActCell::set_grad_fn(act_fn_t fn) {
	_grad = fn;
}

template<typename VT>
const nerone::value_list_t& nerone::ActCell::get_inputs() {
	return _input_value_list;
}

template<typename VT>
const nerone::value_list_t& nerone::ActCell::get_outputs() {
	return _output_value_list;
}

template<typename VT>
void nerone::ActCell::set_inputs(value_list_t vals) {
	set_input(vals[0]);
}

template<typename VT>
void nerone::ActCell::set_outputs(value_list_t vals) {
	set_output(vals[0]);
}

template<typename VT>
void nerone::ActCell::set_input(shared_value_t value) {
	_input_value = value;
}

template<typename VT>
void nerone::ActCell::set_output(shared_value_t value) {
	_output_value = value;
}

template<typename VT>
void calc_value() {
	_output_value->set(_act(_input_value->get()));
}

template<typename VT>
void calc_grad() {
	_input_value->set_grad(_grad(_input_value->get()) * _output_value->get_grad());
}

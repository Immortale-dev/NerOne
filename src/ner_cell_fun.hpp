template<typename VT, typename FN>
nerone::cell::Functional<VT>::Functional() : Functional(std::make_shared<VT>(), std::make_shared<VT>(), activation::linear::fun, activation::linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT>::Functional(shared_value_t input, shared_value_t output) : Functional(input, output, activation::linear::fun, activation::linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT>::Functional(FN act, FN grad) : Functional(std::make_shared<VT>(), std::make_shared<VT>(), act, grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT>::Functional(shared_value_t input, FN act, FN grad) : Functional(input, std::make_shared<VT>(), activation::linear::fun, activation::linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT>::Functional(shared_value_t input, shared_value_t output, FN act, FN grad) :
	_input_value(input),
	_output_value(output),
	_input_value_list(1, _input_value),
	_output_value_list(1, _output_value),
	_act(act),
	_grad(grad)
{}

template<typename VT, typename FN>
FN nerone::cell::Functional<VT>::get_act_fn() {
	return _act;
}

template<typename VT, typename FN>
FN nerone::cell::Functional<VT>::get_grad_fn() {
	return _grad;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_act_fn(FN fn) {
	_act = fn;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_grad_fn(FN fn) {
	_grad = fn;
}

template<typename VT, typename FN>
const nerone::value_list_t& nerone::cell::Functional<VT>::get_inputs() {
	return _input_value_list;
}

template<typename VT, typename FN>
const nerone::value_list_t& nerone::cell::Functional<VT>::get_outputs() {
	return _output_value_list;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_inputs(value_list_t vals) {
	set_input(vals[0]);
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_outputs(value_list_t vals) {
	set_output(vals[0]);
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_input(shared_value_t value) {
	_input_value = value;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::set_output(shared_value_t value) {
	_output_value = value;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT>::clean() {
	this->cast_value(_input_value)->clean();
	this->cast_value(_output_value)->clean();
}

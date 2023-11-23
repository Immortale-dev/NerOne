template<typename VT, typename FN>
nerone::cell::Functional<VT,FN>::Functional() : Functional(std::make_shared<VT>(), std::make_shared<VT>(), activation::Linear::fun, activation::Linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT,FN>::Functional(shared_value_t input, shared_value_t output) : Functional(input, output, activation::Linear::fun, activation::Linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT,FN>::Functional(FN act, FN grad) : Functional(std::make_shared<VT>(), std::make_shared<VT>(), act, grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT,FN>::Functional(shared_value_t input, FN act, FN grad) : Functional(input, std::make_shared<VT>(), activation::Linear::fun, activation::Linear::grad) {}

template<typename VT, typename FN>
nerone::cell::Functional<VT,FN>::Functional(shared_value_t input, shared_value_t output, FN act, FN grad) :
	_input_value(input),
	_output_value(output),
	_input_value_list(1, _input_value),
	_output_value_list(1, _output_value),
	_act(act),
	_grad(grad)
{}

template<typename VT, typename FN>
FN nerone::cell::Functional<VT,FN>::get_act_fn() {
	return _act;
}

template<typename VT, typename FN>
FN nerone::cell::Functional<VT,FN>::get_grad_fn() {
	return _grad;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_act_fn(FN fn) {
	_act = fn;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_grad_fn(FN fn) {
	_grad = fn;
}

template<typename VT, typename FN>
const nerone::value_list_t& nerone::cell::Functional<VT,FN>::get_inputs() {
	return _input_value_list;
}

template<typename VT, typename FN>
const nerone::value_list_t& nerone::cell::Functional<VT,FN>::get_outputs() {
	return _output_value_list;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_inputs(value_list_t vals) {
	set_input(vals[0]);
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_outputs(value_list_t vals) {
	set_output(vals[0]);
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_input(shared_value_t value) {
	_input_value = value;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::set_output(shared_value_t value) {
	_output_value = value;
}

template<typename VT, typename FN>
void nerone::cell::Functional<VT,FN>::clean() {
	this->cast_value(_input_value)->clean();
	this->cast_value(_output_value)->clean();
}

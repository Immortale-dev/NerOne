template<typename VT>
void nerone::cell::Activation<VT>::calc_value() {
	_output_value->set(_act(_input_value->get()));
}

template<typename VT>
void nerone::cell::Activation<VT>::calc_grad() {
	_input_value->set_grad(_grad(_input_value->get()) * _output_value->get_grad());
}

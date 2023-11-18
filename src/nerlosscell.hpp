template<typename VT>
void nerone::ActCell<VT>::calc_value() {
	_output_value->set(_act(_input_value->get(), _expected_value->get()));
}

template<typename VT>
void nerone::ActCell<VT>::calc_value(VT::f_type expected) {
	_expected_value.set(expected);
	calc_value();
}

template<typename VT>
void nerone::ActCell<VT>::calc_grad() {
	_input_value->set_grad(_grad(_input_value->get()) * _output_value->get_grad());
}

template<typename VT>
void nerone::ActCell<VT>::clean() {
	FunCell<VT, nerone::loss_fn_t>::clean();
	_expected_value->clean();
}

template<typename VT>
void nerone::ActCell<VT>::set_expected_value(shared_value_t val) {
	_expected_value = val;
}

template<typename VT>
nerone::shared_value_t nerone::ActCell<VT>::get_expected_value() {
	return _expected_value;
}

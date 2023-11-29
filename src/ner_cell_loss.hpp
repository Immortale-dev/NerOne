template<typename VT>
void nerone::cell::Loss<VT>::calc_value() {
	this->cast_value(this->_output_value)->set(
		this->_act(this->cast_value(this->_input_value)->get(), this->cast_value(_expected_value)->get())
	);
}

template<typename VT>
void nerone::cell::Loss<VT>::calc_value(typename value_type::f_type expected) {
	this->cast_value(_expected_value)->set(expected);
	calc_value();
}

template<typename VT>
void nerone::cell::Loss<VT>::calc_grad() {
	this->cast_value(this->_input_value)->set_grad(
		this->_grad(this->cast_value(this->_input_value)->get(), this->cast_value(_expected_value)->get())
	);
}

template<typename VT>
void nerone::cell::Loss<VT>::clean() {
	Functional<VT, nerone::loss_fn_t<typename value_type::f_type>>::clean();
	this->cast_value(_expected_value)->clean();
}

template<typename VT>
void nerone::cell::Loss<VT>::set_expected_value(shared_value_t val) {
	_expected_value = val;
}

template<typename VT>
nerone::shared_value_t nerone::cell::Loss<VT>::get_expected_value() {
	return _expected_value;
}

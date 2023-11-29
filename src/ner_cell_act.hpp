template<typename VT>
void nerone::cell::Activation<VT>::calc_value() {
	this->cast_value(this->_output_value)->set(this->_act(this->cast_value(this->_input_value)->get()));
}

template<typename VT>
void nerone::cell::Activation<VT>::calc_grad() {
	this->cast_value(this->_input_value)->set_grad(
		this->_grad(this->cast_value(this->_input_value)->get()) * this->cast_value(this->_output_value)->get_grad()
	);
}

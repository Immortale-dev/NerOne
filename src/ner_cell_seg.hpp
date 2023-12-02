template<typename VT>
nerone::cell::Segment<VT>::Segment(value_list_t inputs, value_list_t outputs) : _input_values(inputs), _output_values(outputs) {
	rebuild_weights();
}

template<typename VT>
const nerone::value_list_t& nerone::cell::Segment<VT>::get_inputs() {
	return _input_values;
}

template<typename VT>
const nerone::value_list_t& nerone::cell::Segment<VT>::get_outputs() {
	return _output_values;
}

template<typename VT>
void nerone::cell::Segment<VT>::set_inputs(value_list_t vals) {
	_input_values = vals;
	rebuild_weights();
}

template<typename VT>
void nerone::cell::Segment<VT>::set_outputs(value_list_t vals) {
	_output_values = vals;
	rebuild_weights();
}

template<typename VT>
void nerone::cell::Segment<VT>::calc_value() {
	for (size_t i=0;i<_output_values.size();i++) {
		f_type res = 0;
		for (size_t j=0;j<_input_values.size();j++) {
			res += this->cast_value(_input_values[j])->get() * _weights[_input_values.size()*i+j];
		}
		this->cast_value(_output_values[i])->set(res);
	}
}

template<typename VT>
void nerone::cell::Segment<VT>::calc_grad() {
	weight_list_t grads(_input_values.size());
	for (size_t i=0;i<_input_values.size();i++) {
		f_type res = 0;
		for(size_t j=0;j<_output_values.size();j++) {
			res += this->cast_value(_output_values[j])->get_grad() * _weights[_input_values.size()*j+i];
		}
		grads[i] = res;
	}
	for (size_t i=0;i<_input_values.size();i++) {
		for(size_t j=0;j<_output_values.size();j++) {
			_grads[_input_values.size()*j+i] += this->cast_value(_input_values[i])->get() * this->cast_value(_output_values[j])->get_grad();
		}
	}
	for(size_t i=0;i<_input_values.size();i++) {
		this->cast_value(_input_values[i])->set_grad(grads[i]);
	}
}

template<typename VT>
void nerone::cell::Segment<VT>::clean() {
	std::memset(_grads.data(), 0, sizeof(f_type) * _input_values.size() * _output_values.size());
}

template<typename VT>
void nerone::cell::Segment<VT>::update(shared_train_data_t data) {
	const auto rate = std::static_pointer_cast<GDTrainData>(data)->rate;
	for (size_t i=0;i<_input_values.size();i++) {
		for(size_t j=0;j<_output_values.size();j++) {
			_weights[_input_values.size()*j+i] += _grads[_input_values.size()*j+i] * rate;
		}
	}
	clean();
}

template<typename VT>
const typename nerone::cell::Segment<VT>::weight_list_t& nerone::cell::Segment<VT>::get_weights() {
	return _weights;
}

template<typename VT>
void nerone::cell::Segment<VT>::set_weights(weight_list_t weights) {
	const size_t sz = sizeof(f_type) * std::min(_weights.size(), weights.size());
	std::memcpy(_weights.data(), weights.data(), sz);
}

template<typename VT>
void nerone::cell::Segment<VT>::rebuild_weights() {
	const size_t sz = _input_values.size()*_output_values.size();
	_weights.resize(sz);
	_grads.resize(sz);
}

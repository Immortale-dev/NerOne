template<typename VT>
nerone::SegmentCell<VT>::SegmentCell(value_list_t inputs, value_list_t outputs) : _input_values(inputs), _output_values(output) {
	rebuild_weights();
}

template<typename VT>
const nerone::value_list_t& nerone::SegmentCell<VT>::get_inputs() {
	return _input_values;
}

template<typename VT>
const nerone::value_list_t& nerone::SegmentCell<VT>::get_outputs() {
	return _output_values;
}

template<typename VT>
void nerone::SegmentCell<VT>::set_inputs(value_list_t vals) {
	_input_values = vals;
	rebuild_weights();
}

template<typename VT>
void nerone::SegmentCell<VT>::set_outputs(value_list_t vals) {
	_output_values = vals;
	rebuild_weights();
}

template<typename VT>
void nerone::SegmentCell<VT>::calc_values() {
	for (size_t i=0;i<_output_values.size();i++) {
		VT::f_type res = 0;
		for (size_t j=0;j<_input_values.size();j++) {
			res += _input_values[j].get() * _weights[_input_values.size()*i+j];
		}
		_output_values[i].set(res);
	}
}

template<typename VT>
void nerone::SegmentCell<VT>::calc_grads() {
	weight_list_t grads(_input_values.size());
	for (size_t i=0;i<_input_values.size();i++) {
		VT::f_type res = 0;
		for(size_t j=0;j<_output_values.size();j++) {
			res += _output_values[j].get_grad() * _weights[_input_values.size()*j+i];
		}
		grads[i] = res;
	}
	for (size_t i=0;i<_input_values.size();i++) {
		for(size_t j=0;j<_output_values.size();j++) {
			_grads[_input_values.size()*j+i] += _input_values[i].get() * _output_values[j].get_grad();
		}
	}
	for(size_t i=0;i<_input_values.size();i++) {
		_input_values[i].set_grad(grad[i]);
	}
}

template<typename VT>
void nerone::SegmentCell<VT>::start() {
	std::memset(_grad.data(), 0, sizeof(VT::f_type) * _input_values.size() * _output_values.size());
}

template<typename VT>
void nerone::SegmentCell<VT>::finish() {}

template<typename VT>
void nerone::SegmentCell<VT>::update(shared_train_data_t data) {
	const auto ratio = std::static_pointer_cast<GDTrainData>(data)->ratio;
	for (size_t i=0;i<_input_values.size();i++) {
		for(size_t j=0;j<_output_values.size();j++) {
			_weights[_input_values.size()*j+i] += _grads[_input_values.size()*j+i] * ratio;
		}
	}
}

template<typename VT>
const nerone::SegmentCell<VT>::weight_list_t& nerone::SegmentCell<VT>::get_weights() {
	return _weights;
}

template<typename VT>
void nerone::SegmentCell<VT>::set_weights(weight_list_t weights) {
	const size_t sz = sizeof(VT::f_type) * std::min(_weights.size(), weights.size());
	std::memcpy(_weights.data(), weigts.data(), sz);
}

template<typename VT>
void nerone::SegmentCell<VT>::rebuild_weights() {
	const size_t sz = _input_values.size()*_output_values.size();
	_weights.resize(sz);
	_grads.resize(sz);
}

template<typename VT>
nerone::cell::LossLayer<VT>::LossLayer(cell_list_t cells) : Layer<VT>(cells) {
	reassign_expected_values();
}

template<typename VT>
const nerone::value_list_t& nerone::cell::LossLayer<VT>::get_expected_inputs() {
	return _expected_value_list;
}

template<typename VT>
void nerone::cell::LossLayer<VT>::set_expected_inputs(value_list_t list) {
	size_t ind = 0;
	for(auto cell : this->_cells) {
		std::static_pointer_cast<Loss<VT>>(cell)->set_expected_value(list[ind++]);
	}
	reassign_expected_values();
}

template<typename VT>
void nerone::cell::LossLayer<VT>::reassign_values() {
	Layer<VT>::reassign_values();
	reassign_expected_values();
}

template<typename VT>
void nerone::cell::LossLayer<VT>::reassign_expected_values() {
	_expected_value_list.resize(0);
	for(auto cell : this->_cells) {
		_expected_value_list.push_back(std::static_pointer_cast<Loss<VT>>(cell)->get_expected_value());
	}
}

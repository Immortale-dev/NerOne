template<typename VT>
nerone::LossLayerCell<VT>::LossLayerCell(cell_list_t cells) : LayerCell<VT>(cells) {}

template<typename VT>
const nerone::value_list_t& nerone::LossLayerCell<VT>::get_expected_inputs() {
	return _expected_value_list;
}

template<typename VT>
void nerone::LossLayerCell<VT>::set_expected_inputs(value_list_t list) {
	size_t ind = 0;
	for(auto cell : _cells) {
		std::static_pointer_cast<LossCell<VT>>(cell)->set_expected_value(list[ind++]);
	}
	reassign_expected_values();
}

template<typename VT>
void nerone::LossLayerCell<VT>::reassign_values() {
	LayerCell<VT>::reassign_values();
	reassign_expected_values();
}

template<typename VT>
void nerone::LossLayerCell<VT>::reassign_expected_values() {
	_expected_value_list.resize(0);
	for(auto cell : _cells) {
		_expected_value_list.push_back(std::static_pointer_cast<LossCell<VT>>(cell)->get_expected_value());
	}
}
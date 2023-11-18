template<typename VT>
nerone:LayerCell<VT>::LayerCell(cell_list_t cells) : ClusterCell<VT>(cells) {}

template<typename VT>
const nerone::value_list_t& nerone::LayerCell<VT>::get_inputs() {
	return _input_value_list;
}

template<typename VT>
const nerone::value_list_t& nerone::LayerCell<VT>::get_outputs() {
	return _output_value_list;
}

template<typename VT>
void nerone::LayerCell<VT>::set_inputs(value_list_t vals) {
	size_t begin = 0;
	for(auto cell : _cells) {
		size_t end = std::min(vals.size(), begin + cell->get_inputs().size());
		cell->set_inputs(value_list_t(vals.begin()+start, vals.begin()+end));
		if(end >= vals.size()) break;
		begin = end;
	}
	reassign_values();
}

template<typename VT>
void nerone::LayerCell<VT>::set_outputs(value_list_t vals) {
	size_t begin = 0;
	for(auto cell : _cells) {
		size_t end = std::min(vals.size(), begin + cell->get_inputs().size());
		cell->set_outputs(value_list_t(vals.begin()+start, vals.begin()+end));
		if(end >= vals.size()) break;
		begin = end;
	}
}

template<typename VT>
void nerone::LayerCell<VT>::reassign_values() {
	_input_value_list.resize(0);
	_output_value_list.resize(0);
	
	for(auto cell : _cells) {
		for(auto val : cell->get_inputs()) {
			_input_value_list.push_back(val);
		}
		for(auto val : cell->get_outputs()) {
			_output_value_list.push_back(val);
		}
	}
}
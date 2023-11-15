template<typename VT>
nerone::SequenceCell<VT>::SequenceCell(cell_list_t cells) : _cells(cells) {
	assign_values();
}

template<typename VT>
const nerone::value_list_t& nerone::SequenceCell<VT>::get_inputs() {
	return _cells[0].inputs();
}

template<typename VT>
const nerone::value_list_t& nerone::SequenceCell<VT>::get_outputs() {
	return _cells[_cells.size()-1].outputs();
}

template<typename VT>
void nerone::SequenceCell<VT>::set_inputs(value_list_t vals) {
	_cells[0].set_inputs(vals);
}

template<typename VT>
void nerone::SequenceCell<VT>::set_outputs(value_list_t vals) {
	_cells[_cells.size()-1].set_outputs(vals);
}

template<typename VT>
void nerone::SequenceCell<VT>::calc_value() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell>(cell)->calc_value();
	}
}

template<typename VT>
void nerone::SequenceCell<VT>::calc_grad() {
	for(size_t i=_cell.size()-1;i>=0;i--) {
		auto cell = _cells[i];
		std::static_pointer_cast<OCell>(cell)->calc_grad();
	}
}

template<typename VT>
void nerone::SequenceCell<VT>::start() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell>(cell)->start();
	}
}

template<typename VT>
void nerone::SequenceCell<VT>::finish() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell>(cell)->finish();
	}
}

template<typename VT>
const nerone::cell_list_t& nerone::SequenceCell<VT>::get_cells() {
	return _cells;
}

template<typename VT>
void nerone::SequenceCell<VT>::set_cells(cell_list_t cells) {
	_cells = cells;
	assign_values();
}

template<typename VT>
const nerone::cell_list_t& nerone::SequenceCell<VT>::update(shared_train_data_t data) {
	for(auto& cell : _cells) {
		auto tcell = std::dynamic_pointer_cast<TCell>(cell);
		if (!tcell) {
			continue;
		}
		tcell->update(data);
	}
}

template<typename VT>
void nerone::SequenceCell<VT>::set_weights(weight_list_t weights) {}

template<typename VT>
const nerone::SequenceCell<VT>::weight_list_t& nerone::SequenceCell<VT>::get_weights() {
	return _weights;
}

template<typename VT>
void nerone::SequenceCell<VT>::assign_values() {
	for(size_t i=0;i<_cells.size()-1;i++) {
		_cells[i+1]->set_inputs(_cells[i]->get_outputs());
	}
}

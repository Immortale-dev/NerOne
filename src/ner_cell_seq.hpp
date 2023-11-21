template<typename VT>
nerone::cell::Sequence<VT>::Sequence(cell_list_t cells) : Cluster<VT>(cells) {
	reassign_values();
}

template<typename VT>
const nerone::value_list_t& nerone::cell::Sequence<VT>::get_inputs() {
	return _cells[0].inputs();
}

template<typename VT>
const nerone::value_list_t& nerone::cell::Sequence<VT>::get_outputs() {
	return _cells[_cells.size()-1].outputs();
}

template<typename VT>
void nerone::cell::Sequence<VT>::set_inputs(value_list_t vals) {
	_cells[0].set_inputs(vals);
}

template<typename VT>
void nerone::cell::Sequence<VT>::set_outputs(value_list_t vals) {
	_cells[_cells.size()-1].set_outputs(vals);
}

template<typename VT>
void nerone::cell::Sequence<VT>::reassign_values() {
	for(size_t i=0;i<_cells.size()-1;i++) {
		_cells[i+1]->set_inputs(_cells[i]->get_outputs());
	}
}

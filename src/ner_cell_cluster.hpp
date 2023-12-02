template<typename VT>
nerone::cell::Cluster<VT>::Cluster(cell_list_t cells) : _cells(cells) {
	reassign_tcells();
}

template<typename VT>
const typename nerone::cell::Cluster<VT>::weight_list_t& nerone::cell::Cluster<VT>::get_weights() {
	return _weights;
}

template<typename VT>
void nerone::cell::Cluster<VT>::set_weights(weight_list_t weights) {}

template<typename VT>
void nerone::cell::Cluster<VT>::clean() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->clean();
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::calc_value() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->calc_value();
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::calc_grad() {
	for(size_t i=_cells.size();i>0;i--) {
		std::static_pointer_cast<OCell<VT>>(_cells[i-1])->calc_grad();
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::start() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->start();
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::finish() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->finish();
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::command(shared_cell_command_t com) {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->command(com);
	}
}

template<typename VT>
void nerone::cell::Cluster<VT>::update(shared_train_data_t data) {
	for(auto& cell : _tcells) {
		std::static_pointer_cast<TCell<VT>>(cell)->update(data);
	}
}

template<typename VT>
const nerone::cell_list_t& nerone::cell::Cluster<VT>::get_cells() {
	return _cells;
}

template<typename VT>
void nerone::cell::Cluster<VT>::set_cells(cell_list_t cells) {
	_cells = cells;
	reassign_tcells();
	reassign_values();
}

template<typename VT>
void nerone::cell::Cluster<VT>::reassign_tcells() {
	_tcells.resize(0);
	for(auto& cell : _cells) {
		auto tcell = std::dynamic_pointer_cast<TCell<VT>>(cell);
		if (tcell) {
			_tcells.push_back(tcell);
		}
	}
}

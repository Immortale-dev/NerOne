template<typename VT>
nerone::ClusterCell<VT>::ClusterCell(cell_list_t cells) : _cells(cells) {
	reassign_tcells();
	reassign_values();
}

template<typename VT>
const nerone::weight_list_t& nerone::ClusterCell<VT>::get_weights() {
	return _weights;
}

template<typename VT>
void nerone::ClusterCell<VT>::set_weights(weight_list_t weights) {}

template<typename VT>
void nerone::ClusterCell<VT>::clean() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->clean();
	}
}

template<typename VT>
void nerone::ClusterCell<VT>::calc_value() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->calc_value();
	}
}

template<typename VT>
void nerone::ClusterCell<VT>::calc_grad() {
	for(size_t i=_cell.size()-1;i>=0;i--) {
		std::static_pointer_cast<OCell>(_cells[i])->calc_grad();
	}
}

template<typename VT>
void nerone::ClusterCell<VT>::start() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->start();
	}
}

template<typename VT>
void nerone::ClusterCell<VT>::finish() {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->finish();
	}
}

template<typename VT>
void nerone::ClusterCell<VT>::command(shared_command_cell_t com) {
	for(auto& cell : _cells) {
		std::static_pointer_cast<OCell<VT>>(cell)->command(com);
	}
}

template<typename VT>
void update(shared_train_data_t data) {
	for(auto& cell : _tcells) {
		std::static_pointer_cast<TCell<VT>>(cell)->update(data);
	}
}

const nerone::cell_list_t& nerone::ClusterCell<VT>::get_cells() {
	return _cells;
}

void nerone::ClusterCell<VT>::set_cells(cell_list_t cells) {
	_cells = cells;
	reassign_tcells();
	reassign_values();
}

void nerone::ClusterCell<VT>::reassign_tcells() {
	_tcells.resize(0);
	for(auto& cell : _cells) {
		auto tcell = std::dynamic_pointer_cast<TCell<VT>>(cell);
		if (tcell) {
			_tcells.push_back(tcell);
		}
	}
}

#include <memory>

#include "nerconvseg.hpp"

nerone::ConvSegment::ConvSegment() {}

nerone::ConvSegment::ConvSegment(cell_list_t begins, cell_list_t ends) : _begins(begins), _ends(ends) {
	_gradients.resize(_begins.size());
	_inputs.resize(_begins.size());
	_outputs.resize(_ends.size());
	for(size_t i=0;i<_begins.size();i++) {
		_inputs[i] = _begins[i]->inputs()[0];
	}
	for(size_t i=0;i<_ends.size();i++) {
		_outputs[i] = _ends[i]->outputs()[0];
	}
}

nerone::value_list_t& nerone::ConvSegment::inputs() {
	return _inputs;
}

nerone::value_list_t& nerone::ConvSegment::outputs() {
	return _outputs;
}

void nerone::ConvSegment::set_begins(cell_list_t begins) {
	_begins = begins;
	_gradients.resize(_begins.size());
	_inputs.resize(begins.size());
	size_t i=0;
	for(auto& cell : begins) {
		_inputs[i++] = cell->inputs()[0];
	}
}

void nerone::ConvSegment::set_ends(cell_list_t ends) {
	_ends = ends;
	_outputs.resize(ends.size());
	size_t i=0;
	for(auto& cell : ends) {
		_outputs[i++] = cell->outputs()[0];
	}
}

nerone::cell_list_t& nerone::ConvSegment::get_begins() {
	return _begins;
}

nerone::cell_list_t& nerone::ConvSegment::get_ends() {
	return _ends;
}

nerone::shared_cell_t nerone::ConvSegment::get_next() {
	return _next;
}

void nerone::ConvSegment::set_next(shared_cell_t cell) {
	_next = cell;
}

void nerone::ConvSegment::calc_values() {
	for(auto cell : _ends) {
		auto value = cell->inputs()[0];
		data_t res = 0;
		auto inputValue = std::static_pointer_cast<InputValue>(value);
		for(auto syn : inputValue->get_syns()) {
			res += syn->get_weight() * syn->get_value()->get();
		}
		res += inputValue->get_bias();
		value->set(res);
		if (cell->type == CellType::ConvActCell) {
			auto convActCell = std::static_pointer_cast<ConvActCell>(cell);
			convActCell->calc_values();
			continue;
		}
		throw std::logic_error("Not supported cell type.");
	}
}

void nerone::ConvSegment::calc_gradients() {
	for(auto &cell : _ends) {
		if (cell->type == CellType::ConvActCell) {
			auto convActCell = std::static_pointer_cast<ConvActCell>(cell);
			convActCell->calc_gradients();
			continue;
		}
		throw std::logic_error("Not supported cell type.");
	}
	
	for(size_t i=0;i<_begins.size();i++) {
		data_t res = 0;
		for(auto& cell : _ends) {
			res += cell->inputs()[0]->get_grad() * cell->inputs()[0]->get_syns()[i];
		}
		_begins[i]->outputs()[0]->set_grad(res);
	}
}

nerone::data_list_t& nerone::ConvSegment::get_gradients() {
	return _gradients;
}

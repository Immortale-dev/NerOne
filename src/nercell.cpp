#include "nercell.hpp"

nerone::value_list_t& nerone::Cell::inputs() {
	return _inputs;
}

nerone::value_list_t& nerone::Cell::outputs() {
	return _outputs;
}

nerone::CellType::Type nerone::Cell::type() {
	return _type;
}

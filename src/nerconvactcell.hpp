#ifndef NN_NER_CONVACT_CELL
#define NN_NER_CONVACT_CELL

#include "nerhelp.hpp"
#include "nercell.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(CONVACT);
	}
	
	/**
	 * A cell with 1 input and 1 output.
	 * This cell combines convolutional and activation cells to create a more convinient structure.
	 */
	class ConvActCell : public Cell {
		public:
			ConvActCell();
			ConvActCell(shared_cell_t conv, shared_cell_t act);
			shared_cell_t get_conv();
			shared_cell_t get_act();
			void set_conv(shared_cell_t cell);
			void set_act(shared_cell_t cell);
			value_list_t& inputs();
			value_list_t& outputs();
			
		protected:
			auto type = CellType::CONVACT;
			shared_cell_t _conv, _act;
	};

}

#endif // NN_NER_CONVACT_CELL

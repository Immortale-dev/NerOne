#ifndef NN_CONV_SEGMENT
#define NN_CONV_SEGMENT

#include "nerhelp.hpp"
#include "nercell.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(CONVSEGMENT);
	}
	
	/**
	 * A cell with multiple inputs and multiple outputs.
	 * Main purpose of this cell is to combine multiple convolutional activation cells into logical layers.
	 */
	class ConvSegment : public Cell {
		public:
			ConvSegment();
			ConvSegment(cell_list_t inputs, cell_list_t outputs);
			value_list_t& inputs();
			value_list_t& outputs();
			void set_begins(cell_list_t begins);
			void set_ends(cell_list_t ends);
			cell_list_t& get_begins();
			cell_list_t& get_ends();
			virtual void calc_values();
			virtual void calc_gradients();
			
		protected:
			auto type = CellType::CONVSEGMENT;
			cell_list_t _inputs, _outputs;
			shared_cell_t _next;
			data_list_t _gradients;
	};

}

#endif // NN_CONV_SEGMENT
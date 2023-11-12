#ifndef NN_NER_SEQ_CELL
#define NN_NER_SEQ_CELL

#include "nerhelp.hpp"
#include "nerocell.h"

namespace nerone {
	/**
	 * A sequense cell.
	 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
	 */
	template<typename VT>
	class SeqCell : public OCell {
		public:
			using value_type = VT;
			
			SeqCell() = default;
			SeqCell(cell_list_t cells);
			
			const value_list_t& get_inputs();
			const value_list_t& get_outputs();
			void set_inputs(value_list_t vals);
			void set_outputs(value_list_t vals);
			void calc_value();
			void calc_grad();
			
			void set_cells(cell_list_t cells);
			const cell_list_t& get_cells();
			
		protected:
			value_list_t _input_value_list;
			value_list_t _output_value_list;
			cell_list_t _cells;
	};

}

#endif // NN_NER_SEQ_CELL

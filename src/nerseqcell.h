#ifndef NN_NER_SEQ_CELL
#define NN_NER_SEQ_CELL

#include "nerhelp.hpp"
#include "nerocell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(COLLECTION);
	}
	/**
	 * A sequense cell.
	 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
	 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
	 */
	template<typename VT>
	class SequenceCell : public TCell<VT> {
		public:
			using value_type = VT;
			using weight_list_t = TCell<VT>::weight_list_t;
			
			SeqCell() = default;
			SeqCell(cell_list_t cells);
			
			const value_list_t& get_inputs();
			const value_list_t& get_outputs();
			void set_inputs(value_list_t vals);
			void set_outputs(value_list_t vals);
			
			void calc_value();
			void calc_grad();
			void start();
			void finish();
			
			void update(shared_train_data_t data);
			void set_weights(weight_list_t weights);
			const weight_list_t& get_weights();
			
			const cell_list_t& get_cells();
			void set_cells(cell_list_t cells);
			
		protected:
			type = CellType::COLLECTION;
			value_list_t _input_value_list;
			value_list_t _output_value_list;
			cell_list_t _cells;
			weight_list_t _weights;
			
		private:
			void assign_values();
	};

}

#include "nerseqcell.hpp"

#endif // NN_NER_SEQ_CELL

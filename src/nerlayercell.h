#ifndef NN_NER_LAYER_CELL
#define NN_NER_LAYER_CELL

#include "nerhelp.hpp"
#include "nerclustercell.h"

namespace nerone {
	/**
	 * A sequense cell.
	 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
	 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
	 */
	template<typename VT>
	class LayerCell : public ClusterCell<VT> {
		public:
			using value_type = VT;
			
			LayerCell() = default;
			LayerCell(cell_list_t cells);
			
			const value_list_t& get_inputs();
			const value_list_t& get_outputs();
			void set_inputs(value_list_t vals);
			void set_outputs(value_list_t vals);
			
		protected:
			void reassign_values();
			
			value_list_t _input_value_list;
			value_list_t _output_value_list;
	};

}

#include "nerlayercell.hpp"

#endif // NN_NER_LAYER_CELL

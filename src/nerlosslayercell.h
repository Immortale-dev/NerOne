#ifndef NN_NER_LOSSLAYER_CELL
#define NN_NER_LOSSLAYER_CELL

#include "nerhelp.hpp"
#include "nerlossclustercell.h"
#include "nerlosscell.h"

namespace nerone {
	/**
	 * A sequense cell.
	 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
	 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
	 */
	template<typename VT>
	class LossLayerCell : public LayerCell<VT>, public LossClusterCell<VT> {
		public:
			using value_type = VT;
			
			LossLayerCell(cell_list_t cells);
			
			const value_list_t& get_expected_inputs();
			void set_expected_inputs(value_list_t vals);
			
		protected:
			void reassign_values();
			void reassign_expected_values();
			
			value_list_t _expected_value_list;
	};
}

#include "nerlosslayercell.hpp"

#endif // NN_NER_LOSSLAYER_CELL

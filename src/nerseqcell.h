#ifndef NN_NER_SEQ_CELL
#define NN_NER_SEQ_CELL

#include "nerhelp.hpp"
#include "nerclustercell.h"

namespace nerone {
	/**
	 * A sequense cell.
	 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
	 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
	 */
	template<typename VT>
	class SequenceCell : public ClusterCell<VT> {
		public:
			using value_type = VT;
			using weight_list_t = TCell<VT>::weight_list_t;
			
			SequenceCell() = default;
			SequenceCell(cell_list_t cells);
			
			const value_list_t& get_inputs();
			const value_list_t& get_outputs();
			void set_inputs(value_list_t vals);
			void set_outputs(value_list_t vals);
			
		protected:
			void reassign_values();
	};

}

#include "nerseqcell.hpp"

#endif // NN_NER_SEQ_CELL
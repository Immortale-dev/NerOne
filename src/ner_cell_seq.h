#ifndef _NN_NER_CELL_SEQ
#define _NN_NER_CELL_SEQ

#include "ner_help.h"
#include "ner_cell_cluster.h"

namespace nerone {
	namespace cell {
		/**
		 * A cluster cell.
		 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
		 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
		 */
		template<typename VT>
		class Sequence : public Cluster<VT> {
			public:
				using value_type = VT;
				using weight_list_t = typename TCell<VT>::weight_list_t;
				
				Sequence() = default;
				Sequence(cell_list_t cells);
				
				const value_list_t& get_inputs();
				const value_list_t& get_outputs();
				void set_inputs(value_list_t vals);
				void set_outputs(value_list_t vals);
				
				void connect_cells();
				
			protected:
				void reassign_values() override;
		};
	}
}

#include "ner_cell_seq.hpp"

#endif // _NN_NER_CELL_SEQ

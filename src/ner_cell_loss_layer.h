#ifndef _NN_NER_CELL_LOSS_LAYER
#define _NN_NER_CELL_LOSS_LAYER

#include "ner_help.h"
#include "ner_cell_loss.h"
#include "ner_cell_loss_cluster.h"
#include "ner_cell_layer.h"

namespace nerone {
	namespace cell {
		/**
		 * A sequense cell.
		 * The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.
		 * Note, outputs from previous cell will be automatically assigned to inputs of the next cell.
		 */
		template<typename VT>
		class LossLayer : public Layer<VT>, public LossClusterInterface {
			public:
				using value_type = VT;
				
				LossLayer(cell_list_t cells);
				
				const value_list_t& get_expected_inputs();
				void set_expected_inputs(value_list_t vals);
				
			protected:
				void reassign_values();
				void reassign_expected_values();
				
				value_list_t _expected_value_list;
		};
	}
}

#include "ner_cell_loss_layer.hpp"

#endif // _NN_NER_CELL_LOSS_LAYER

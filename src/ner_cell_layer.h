#ifndef _NN_NER_CELL_LAYER
#define _NN_NER_CELL_LAYER

#include "ner_help.h"
#include "ner_cell_cluster.h"

namespace nerone {
	namespace cell {
		/**
		 * A cluster cell that connects keep cells to be executed in paralel,
		 * making its inputs to be all the inputs of all sent cells, and its
		 * outputs to be all the outputs from all cells.
		 */
		template<typename VT>
		class Layer : public Cluster<VT> {
			public:
				using value_type = VT;
				
				Layer() = default;
				Layer(cell_list_t cells);
				
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
}

#include "ner_cell_layer.hpp"

#endif // _NN_NER_CELL_LAYER

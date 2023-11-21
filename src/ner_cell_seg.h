#ifndef _NN_CELL_SEGMENT
#define _NN_CELL_SEGMENT

#include <stdexcept>
#include <cstring>
#include <algorithm>

#include "ner_help.h"
#include "ner_cell_t.h"

namespace nerone {
	namespace cell {
		/**
		 * A cell that works as a connector between abstract layers.
		 * It connects every value of input layer to every value of output
		 * layer using weights creating dense connection.
		 * It calculates output values by summing all inputs values multiplied by
		 * corresponding weight.
		 */
		template<typename VT>
		class Segment : public TCell<VT> {
			public:
				using value_type = VT;
				using weight_list_t = TCell<VT>::weight_list_t;
				
				Segment() = default;
				Segment(value_list_t inputs, value_list_t outputs);
				
				const value_list_t& get_inputs();
				const value_list_t& get_outputs();
				void set_inputs(value_list_t vals);
				void set_outputs(value_list_t vals);
				
				void calc_values();
				void calc_grads();
				void clean();
				
				const weight_list_t& get_weights();
				void set_weights(weight_list_t weights);
				void update(shared_train_data_t data);

			protected:
				value_list_t _input_values;
				value_list_t _output_values;
				weight_list_t _weights;
				weight_list_t _grads;
				
			private:
				void rebuild_weights();
		};
	}
}

#include "ner_cell_seg.hpp"

#endif // _NN_CELL_SEGMENT
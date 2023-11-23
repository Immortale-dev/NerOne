#ifndef _NN_NER_CELL_FUN
#define _NN_NER_CELL_FUN

#include <memory>

#include "ner_help.h"
#include "ner_cell_o.h"
#include "ner_activation_linear.h"

namespace nerone {
	namespace cell {
		/**
		 * A cell with 1 input and 1 output.
		 * Main purpose of this cell is to Apply a function.
		 */
		template<typename VT, typename FN>
		class Functional : public OCell<VT> {
			public:
				using value_type = VT;
				
				Functional();
				Functional(shared_value_t input, shared_value_t output);
				Functional(FN act, FN grad);
				Functional(shared_value_t input, shared_value_t output, FN act, FN grad);
				Functional(shared_value_t input, FN act, FN grad);
				FN get_act_fn();
				FN get_grad_fn();
				void set_act_fn(FN);
				void set_grad_fn(FN);
				const value_list_t& get_inputs();
				const value_list_t& get_outputs();
				void set_inputs(value_list_t vals);
				void set_outputs(value_list_t vals);
				void clean();
				void set_input(shared_value_t value);
				void set_output(shared_value_t value);
				
			protected:
				shared_value_t _input_value;
				shared_value_t _output_value;
				value_list_t _input_value_list;
				value_list_t _output_value_list;
				FN _act;
				FN _grad;
		};
	}
}

#include "ner_cell_fun.hpp"

#endif // _NN_NER_CELL_FUN

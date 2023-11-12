#ifndef NN_NER_ACT_CELL
#define NN_NER_ACT_CELL

#include <memory>

#include "nerhelp.hpp"
#include "nerocell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(ACTIVATION);
	}
	
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply activation function.
	 */
	template<typename VT>
	class ActCell : public OCell {
		public:
			using value_type = VT;
			
			ActCell();
			ActCell(shared_value_t input, shared_value_t output);
			ActCell(act_fn_t act, act_fn_t grad);
			ActCell(shared_value_t input, shared_value_t output, act_fn_t act, act_fn_t grad);
			ActCell(shared_value_t input, act_fn_t act, act_fn_t grad);
			act_fn_t get_act_fn();
			act_fn_t get_grad_fn();
			void set_act_fn(act_fn_t);
			void set_grad_fn(act_fn_t);
			const value_list_t& get_inputs();
			const value_list_t& get_outputs();
			void set_inputs(value_list_t vals);
			void set_outputs(value_list_t vals);
			void calc_value();
			void calc_grad();
			void set_input(shared_value_t value);
			void set_output(shared_value_t value);
			
		protected:
			auto type = CellType::ACTIVATION;
			shared_value_t _input_value;
			shared_value_t _output_value;
			value_list_t _input_value_list;
			value_list_t _output_value_list;
			act_fn_t _act;
			act_fn_t _grad;
	};

}

#endif // NN_NER_ACT_CELL

#ifndef NN_NER_FUN_CELL
#define NN_NER_FUN_CELL

#include <memory>

#include "nerhelp.hpp"
#include "nerocell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(FUNCTIONAL);
	}
	
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply a function.
	 */
	template<typename VT, typename FN>
	class FunCell : public OCell<VT> {
		public:
			using value_type = VT;
			
			FunCell();
			FunCell(shared_value_t input, shared_value_t output);
			FunCell(FN act, FN grad);
			FunCell(shared_value_t input, shared_value_t output, FN act, FN grad);
			FunCell(shared_value_t input, FN act, FN grad);
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
			auto type = CellType::FUNCTIONAL;
			shared_value_t _input_value;
			shared_value_t _output_value;
			value_list_t _input_value_list;
			value_list_t _output_value_list;
			FN _act;
			FN _grad;
	};

	#include "nerfuncell.hpp"
}

#endif // NN_NER_FUN_CELL

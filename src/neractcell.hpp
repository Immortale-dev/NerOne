#ifndef NN_NER_ACT_CELL
#define NN_NER_ACT_CELL

#include "nerhelp.hpp"
#include "nercell.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(ACT);
	}
	
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply activation function to the first input connected value.
	 */
	class ActCell : public Cell {
		public:
			ActCell();
			ActCell(shared_value_t val);
			ActCell(shared_value_t val, act_fn_t act, act_fn_t grad);
			shared_value_t& get_value();
			void set_value(shared_value_t value);
			act_fn_t get_act();
			act_fn_t get_grad();
			void set_act(act_fn_t);
			void set_grad(act_fn_t);
			value_list_t& inputs();
			value_list_t& outputs();
			
		protected:
			auto type = CellType::ACT;
			shared_value_t _value;
			value_list_t _value_list;
			act_fn_t _act;
			act_fn_t _grad;
	};

}

#endif // NN_NER_ACT_CELL

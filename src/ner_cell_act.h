#ifndef _NN_NER_CELL_ACT
#define _NN_NER_CELL_ACT

#include <memory>

#include "ner_help.h"
#include "ner_cell_fun.h"

namespace nerone {
	namespace cell {
		/**
		 * A cell with 1 input and 1 output.
		 * Main purpose of this cell is to Apply activation function.
		 */
		template<typename VT>
		class Activation : public Functional<VT, nerone::act_fn_t<typename VT::f_type>> {
			public:
				using value_type = VT;
				
				using Functional<VT, nerone::act_fn_t<typename VT::f_type>>::Functional;
				
				void calc_value();
				void calc_grad();
		};
	}
}

#include "ner_cell_act.hpp"

#endif // _NN_NER_CELL_ACT

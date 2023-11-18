#ifndef NN_NER_ACT_CELL
#define NN_NER_ACT_CELL

#include <memory>

#include "nerhelp.hpp"
#include "nerfuncell.h"

namespace nerone {
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply activation function.
	 */
	template<typename VT>
	class ActCell : public FunCell<VT, nerone::act_fn_t> {
		public:
			using value_type = VT;
			
			void calc_value();
			void calc_grad();
	};

	#include "neractcell.hpp"
}

#endif // NN_NER_ACT_CELL

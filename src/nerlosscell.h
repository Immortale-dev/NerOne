#ifndef NN_NER_LOSS_CELL
#define NN_NER_LOSS_CELL

#include <memory>

#include "nerhelp.hpp"
#include "nerfuncell.h"

namespace nerone {
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply activation function.
	 */
	template<typename VT>
	class ActCell : public FunCell<VT, nerone::loss_fn_t> {
		public:
			using value_type = VT;
			
			void calc_value(VT::f_type expected);
			void calc_value();
			void calc_grad();
			void clean();
			
			void set_expected_value(shared_value_t val);
			shared_value_t get_expected_value();
			
		protected:
			shared_value_t _expected_value;
	};

	#include "nerlosscell.hpp"
}

#endif // NN_NER_LOSS_CELL

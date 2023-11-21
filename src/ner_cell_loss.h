#ifndef NN_NER_LOSS_CELL
#define NN_NER_LOSS_CELL

#include <memory>

#include "ner_help.h"
#include "ner_cell_fun.h"

namespace nerone {
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to Apply loss function.
	 */
	template<typename VT>
	class Loss : public Functional<VT, nerone::loss_fn_t<VT::f_type>> {
		public:
			using value_type = VT;
			
			using Functional<VT, nerone::loss_fn_t<VT::f_type>>::Functional;
			
			void calc_value(VT::f_type expected);
			void calc_value();
			void calc_grad();
			void clean();
			
			void set_expected_value(shared_value_t val);
			shared_value_t get_expected_value();
			
		protected:
			shared_value_t _expected_value;
	};
}

#include "ner_cell_loss.hpp"

#endif // NN_NER_LOSS_CELL

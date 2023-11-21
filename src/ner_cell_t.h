#ifndef _NN_NER_CELL_T
#define _NN_NER_CELL_T

#include <vector>

#include "ner_help.h"
#include "ner_cell_o.h"

namespace nerone {
	namespace cell {
		/**
		 * Trainable cell interface.
		 */
		template<typename VT>
		class TCell : public OCell<VT> {
			public:
				using value_type = VT;
				using weight_list_t = std::vector<f_type>;
				
				virtual const weight_list_t& get_weights() = 0;
				virtual void set_weights(weight_list_t weights) = 0;
				virtual void update(shared_train_data_t data) = 0;
		};
	}
}

#endif // _NN_NER_CELL_T
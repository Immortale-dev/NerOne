#ifndef _NN_CELL_LOSS_CLUSTER
#define _NN_CELL_LOSS_CLUSTER

#include "ner_help.h"
#include "ner_cell_cluster.h"

namespace nerone {
	namespace cell {
		/**
		 * Abstract interface responsible for collecting and calling it's successors
		 * that inherit cell::Loss
		 * corresponding function and redirecting commands.
		 */
		class LossClusterInterface {
			public:
				virtual const value_list_t& get_expected_inputs() = 0;
				virtual void set_expected_inputs(value_list_t vals) = 0;
		};
	}
}

#endif // _NN_CELL_LOSS_CLUSTER

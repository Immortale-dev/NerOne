#ifndef _NN_NER_CELL_CLUSTER
#define _NN_NER_CELL_CLUSTER

#include "ner_help.h"
#include "ner_cell_o.h"
#include "ner_cell_t.h"

namespace nerone {
	namespace cell {
		/**
		 * Abstract class responsible for collecting and calling it's successors
		 * corresponding function and redirecting commands.
		 */
		template<typename VT>
		class Cluster : public TCell<VT> {
			public:
				using value_type = VT;
				using weight_list_t = typename TCell<VT>::weight_list_t;
				
				Cluster() = default;
				Cluster(cell_list_t cells);
				
				void update(shared_train_data_t data);
				void calc_value();
				void calc_grad();
				void clean();
				void start();
				void finish();
				void command(shared_cell_command_t com);
				
				const weight_list_t& get_weights();
				void set_weights(weight_list_t weights);
				
				virtual const cell_list_t& get_cells();
				virtual void set_cells(cell_list_t cells);

			protected:
				virtual void reassign_values() = 0;
				
				weight_list_t _weights;
				cell_list_t _cells;
				cell_list_t _tcells;
				
			private:
				void reassign_tcells();
		};
	}
}

#include "ner_cell_cluster.hpp"

#endif // _NN_NER_CELL_CLUSTER
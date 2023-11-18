#ifndef NN_CLUSTER_CELL
#define NN_CLUSTER_CELL

#include "nerhelp.hpp"
#include "nertcell.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(CLUSTER);
	}
	
	template<typename VT>
	class ClusterCell : public TCell<VT> {
		public:
			using value_type = VT;
			using weight_list_t = TCell<VT>::weight_list_t;
			
			ClusterCell() = default;
			ClusterCell(cell_list_t cells);
			
			void update(shared_train_data_t data);
			void calc_value();
			void calc_grad();
			void clean();
			void start();
			void finish();
			void command(shared_command_cell_t com);
			
			const weight_list_t& get_weights();
			void set_weights(weight_list_t weights);
			
			virtual const cell_list_t& get_cells();
			virtual void set_cells(cell_list_t cells);

		protected:
			virtual void reassign_values() = 0;
		
			auto type = CellType::CLUSTER;
			
			weight_list_t _weights;
			cell_list_t _cells;
			cell_list_t _tcells;
			
		private:
			void reassign_tcells();
	};
}

#include "nerclustercell.hpp"

#endif // NN_CLUSTER_CELL
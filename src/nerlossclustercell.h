#ifndef NN_LOSSCLUSTER_CELL
#define NN_LOSSCLUSTER_CELL

#include "nerhelp.hpp"
#include "nerclustercell.hpp"

namespace nerone {
	template<typename VT>
	class LossClusterCell : public ClusterCell<VT> {
		public:
			using value_type = VT;
			using weight_list_t = ClusterCell<VT>::weight_list_t;
			
			virtual const value_list_t& get_expected_inputs() = 0;
			virtual void set_expected_inputs(value_list_t vals) = 0;

		protected:
			virtual void reassign_values() = 0;
	};
}

#endif // NN_LOSSCLUSTER_CELL
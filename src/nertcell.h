#ifndef NN_NERTCELL
#define NN_NERTCELL

#include <vector>

#include "nerhelp.hpp"
#include "nercelltype.hpp"
#include "nerocell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(TRAINABLE);
	}
	
	template<typename VT>
	class TCell : public OCell<VT> {
		public:
			using value_type = VT;
			using weight_list_t = std::vector<f_type>;
			
			virtual const weight_list_t& get_weights() = 0;
			virtual void set_weights(weight_list_t weights) = 0;
			virtual void update(shared_train_data_t data) = 0;
			
		protected:
			CellType::Type _type = CellType::TRAINABLE;
	}
}

#endif // NN_NERTCELL
#ifndef NN_NERTCELL
#define NN_NERTCELL

#include "nerhelp.hpp"
#include "nercelltype.hpp"
#include "nerocell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(TRAINABLE);
	}
	
	template<typename VT>
	class TCell : public OCell {
		public:
			using value_type = VT;
			virtual void start() = 0;
			virtual void finish() = 0;
			virtual void train(shared_train_data_t data) = 0;
			
		protected:
			CellType::Type _type = CellType::TRAINABLE;
	}
}

#endif // NN_NERTCELL
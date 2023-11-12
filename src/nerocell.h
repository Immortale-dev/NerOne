#ifndef NN_NEROCELL
#define NN_NEROCELL

#include "nerhelp.hpp"
#include "nercelltype.hpp"
#include "nervcell.h"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(OPERATIONAL);
	}
	
	template<typename VT>
	class OCell : public VCell {
		public:
			using value_type = VT;
			virtual void calc_value() = 0;
			virtual void calc_grad() = 0;
			
		protected:
			CellType::Type _type = CellType::OPERATIONAL;
	}
}

#endif // NN_NEROCELL
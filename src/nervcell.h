#ifndef NN_NERVCELL
#define NN_NERVCELL

#include "nerhelp.hpp"
#include "nercelltype.hpp"
#include "nercell.h"

namespace nerone {
	template<typename VT>
	class VCell : public Cell {
		public:
			using value_type = VT;
			
		protected:
			inline std::shared_ptr<VT> cast_value(shared_value_t val) {
				return std::static_pointer_cast<VT>(value);
			}
	}
}

#endif // NN_NERVCELL
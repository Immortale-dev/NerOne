#ifndef NN_NERCELL
#define NN_NERCELL

#include "nerhelp.hpp"
#include "nercelltype.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(BASE);
	}
	
	class Cell {
		public:
			Cell() = default;
			virtual ~Cell() = default;
			virtual value_list_t& inputs();
			virtual value_list_t& outputs();
			CellType::Type type();
			
		protected:
			CellType::Type _type = CellType::base;
			value_list_t _inputs;
			value_list_t _outputs;
	}
}

#endif // NN_NERCELL
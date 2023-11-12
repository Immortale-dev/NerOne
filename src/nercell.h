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
			virtual const value_list_t& get_inputs() = 0;
			virtual const value_list_t& get_outputs() = 0;
			virtual void set_inputs(value_list_t vals) = 0;
			virtual void set_outputs(value_list_t vals) = 0;
			inline CellType::Type type() { return _type; };
			
		protected:
			CellType::Type _type = CellType::BASE;
	}
}

#endif // NN_NERCELL
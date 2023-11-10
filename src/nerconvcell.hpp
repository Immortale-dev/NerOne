#ifndef NN_NER_CONV_G_CELL
#define NN_NER_CONV_G_CELL

#include "nerhelp.hpp"
#include "nercell.hpp"

namespace nerone {
	namespace CellType {
		DEFINE_CELL_TYPE(CONV);
	}
	
	/**
	 * A cell with 1 input and 1 output.
	 * Main purpose of this cell is to sum all of the syn values;
	 * The cell also has bias value that is alwyas added to the result;
	 */
	class ConvCell : public Cell {
		public:
			ConvCell();
			ConvCell(shared_value_t val);
			shared_value_t& get_value();
			void set_value(shared_value_t value);
			value_t get_bias();
			void set_bias(value_t bias);
			value_list_t& inputs();
			value_list_t& outputs();
			
		protected:
			auto type = CellType::CONV;
			shared_value_t _value;
			value_t _bias;
			value_list_t _value_list;
	};

}

#endif // NN_NER_CONV_G_CELL

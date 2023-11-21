#ifndef _NN_NER_CELL
#define _NN_NER_CELL

#include "ner_help.h"

namespace nerone {
	namespace cell {
		/**
		 * Base cell class every other cell should inherit from.
		 */
		class Cell {
			public:
				Cell() = default;
				virtual ~Cell() = default;
				virtual const value_list_t& get_inputs() = 0;
				virtual const value_list_t& get_outputs() = 0;
				virtual void set_inputs(value_list_t vals) = 0;
				virtual void set_outputs(value_list_t vals) = 0;
		};
	}
}

#endif // _NN_NER_CELL

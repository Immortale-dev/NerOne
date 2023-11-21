#ifndef _NN_NER_CELL_O
#define _NN_NER_CELL_O

#include "ner_help.h"
#include "ner_cell_v.h"

namespace nerone {
	namespace cell {
		/**
		 * Virtual operational cell interface.
		 */
		template<typename VT>
		class OCell : public VCell<VT> {
			public:
				using value_type = VT;
				virtual void calc_value() = 0;
				virtual void calc_grad() = 0;
				virtual void clean() = 0;
				virtual void command(shared_cell_command_t command) {}
				virtual void start() {}
				virtual void finish() {}
		};
	}
}

#endif // _NN_NER_CELL_O
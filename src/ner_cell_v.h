#ifndef _NN_NER_CELL_V
#define _NN_NER_CELL_V

#include "ner_help.h"
#include "ner_cell.h"

namespace nerone {
	namespace cell {
		/**
		 * Value cell interface.
		 */
		template<typename VT>
		class VCell : public Cell {
			public:
				using value_type = VT;
				
			protected:
				inline std::shared_ptr<VT> cast_value(shared_value_t val) {
					return std::static_pointer_cast<VT>(val);
				}
		};
	}
}

#endif // _NN_NER_CELL_V
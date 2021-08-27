#ifndef NN_NERNODE
#define NN_NERNODE

#include <vector>
#include <memory>

#include "nerhelp.hpp"
#include "nersyn.hpp"

namespace nerone{

	class NerNode {
		using syn_list_t = std::vector<NerSyn>;
		
		public:
			NerNode();
			virtual ~NerNode();
			value_t get_value();
			void set_value(value_t val);
			
			
		private:
			syn_list_t syns;
			value_t value;
	};
}

#endif // NN_NERNODE

#ifndef NN_NERVALUE
#define NN_NERVALUE

#include "nerhelp.hpp"
#include "nernode.hpp"

namespace nerone {
	/**
	 * Class extends basic Node class and additionally defines
	 * gradient functions that can be used in Gradient Descent back
	 * propagation algorithm.
	 */
	class Value {
		public:
			Value();
			virtual ~Value();
			Value(value_t val);
			value_t get();
			void set(value_t val);
			syn_list_t& get_syns();
			void set_syns(syn_list_t list);

		private:
			value_t val;
			syn_list_t syns;
	};

}

#endif // NN_NERVALUE

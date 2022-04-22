#ifndef NN_NERNODE
#define NN_NERNODE

#include "nerhelp.hpp"
#include "nersyn.hpp"

namespace nerone{
	/**
	 * Base Neural Network node where `value` defines raw sum of previous
	 * layer `outputs` multiplied with specific `weights`.
	 * `output` defined `value` processed by activation function of the
	 * node.
	 * Each node contains a list of `Syn` elements defining weights
	 * for previous layer nodes outputs.
	 */
	class Node {
		public:
			Node();
			Node(value_t val);
			Node(value_t val, act_fn_t fn);
			virtual ~Node();
			value_t get_value();
			void set_value(value_t val);
			act_fn_t& get_act_fn();
			void set_act_fn(act_fn_t fn);
			syn_list_t& get_syns();
			void set_syns(syn_list_t syns);
			value_t get_output();

		protected:
			value_t value;

		private:
			syn_list_t syns;
			act_fn_t act_fn;
	};
}

#endif // NN_NERNODE

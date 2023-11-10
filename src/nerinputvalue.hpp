#ifndef NN_INPUT_VALUE
#define NN_INPUT_VALUE

#include "nervalue.hpp"

namespace nerone {
	/**
	 * Class extends basic value class and additionally defines
	 * syns and bias properties and functions.
	 */
	class InputValue : public GValue {
		public:
			InputValue() = default;
			virtual ~InputValue() = default;
			InputValue(data_t val);
			virtual syn_list_t& get_syns();
			virtual void set_syns(syn_list_t list);
			virtual data_t get_bias();
			virtual void set_bias(data_t val);

		protected:
			data_t _bias;
			syn_list_t _syns;
	};
}

#endif // NN_INPUT_VALUE
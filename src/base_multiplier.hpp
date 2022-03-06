#ifndef NN_BASE_MULTIPLIER
#define NN_BASE_MULTIPLIER

#include "nerhelp.hpp"
#include "nernode.hpp"
#include "nerlayer.hpp"
#include "nercluster.hpp"
#include "matrix.hpp"

namespace nerone {
	
	namespace multipliers {
	
		class BaseMultiplier {
			public:
				void operator () (shared_cluster_t& cluster, value_list_t&& values);
		};
		
	}
	
}

#endif // NN_BASE_MULTIPLIER

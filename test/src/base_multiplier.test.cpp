#include "cluster_helper.cpp"
#include "base_multiplier.hpp"

SCENARIO_START

DESCRIBE("BaseMultiplier", {
	using namespace nerone;
	
	multipliers::BaseMultiplier multiplier;
	
	DESCRIBE("Create a cluster 3N->4N->2N", {
		shared_cluster_t cluster;
		BEFORE_EACH({
			cluster = generate_cluster_342();
		});
		IT("should calculate the cluster with input values = {0.5, 0.6, 0.7}", {
			multiplier(cluster, {0.5, 0.6, 0.7});
			
			auto res_vals = get_last_layer_values(cluster);
			value_list_t expected_vals = {-4.396, 3.336};
			
			for(size_t i=0;i<res_vals.size();i++){
				EXPECT(res_vals[i]).toBeCloseTo(expected_vals[i],0.0000001);
			}
		});
	});
});

SCENARIO_END

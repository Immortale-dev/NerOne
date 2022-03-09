#include "gradient_descent_teacher.hpp"
#include "mean_square_error_loss.hpp"
#include "nergnode.hpp"

SCENARIO_START

DESCRIBE("GradientDescent", {
	using namespace nerone;
	
	teachers::GradientDescent<NerGNode, loss::MeanSquareError> gd;
	multipliers::BaseMultiplier mul;
	
	DESCRIBE("create cluster 3N->2N->2N with biases and question cluster with {1, 4, 5}", {
		shared_cluster_t cluster;
		BEFORE_EACH({
			cluster = generate_cluster_322B();
			mul(cluster, {1.0,4.0,5.0});
		});
		
		IT("should give {0.889551, 0.8004} cluster result", {
			auto res = get_last_layer_values(cluster);
			auto expect = std::vector<value_t>{0.889551, 0.8004};
			
			for(int i=0;i<(int)res.size();i++){
				EXPECT(res[i]).toBeCloseTo(expect[i], 0.000001);
			}
		});
	});
});

SCENARIO_END

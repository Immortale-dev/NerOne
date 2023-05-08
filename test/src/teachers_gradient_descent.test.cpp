#include "teachers_gradient_descent.hpp"
#include "loss_mean_square_error.hpp"
#include "nergnode.hpp"

SCENARIO_START

DESCRIBE("GradientDescent", {
	using namespace nerone;
	
	teachers::GradientDescent<loss::MeanSquareError> gd;
	multipliers::BaseMultiplier<> mul;
	
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
		
		DESCRIBE("train cluster with {0.1, 0.05} values", {
			BEFORE_EACH({
				gd.set_learning_rate(0.01);
				gd(cluster, {0.1, 0.05});
			});
			
			IT("should have weights adjusted in the cluster", {
				
				std::vector<std::vector<std::vector<nerone::value_t>>> expected{
					{},
					{
						{0.0999802, 0.299921, 0.499901, 0.49998},
						{0.199996, 0.399984, 0.59998, 0.499996}
					},
					{
						{0.699235, 0.899228, 0.499224},
						{0.798817, 0.0988071, 0.498801}
					}
				};
				
				auto layers = cluster->get_layers();
				for(size_t i=1;i<layers.size();i++){
					auto nodes = layers[i]->get_nodes();
					for(size_t j=0;j<nodes.size();j++){
						auto syns = nodes[j]->get_syns();
						for(size_t k=0;k<syns.size();k++){
							EXPECT(syns[k]->get_weight()).toBeCloseTo(expected[i][j][k], 0.000001);
						}
					}
				}
				
				TEST_SUCCEED();
			});
		});
		
		DESCRIBE("train cluster 1000 times with {0.1, 0.05} values", {
			nerone::value_t initial_error;
			BEFORE_EACH({
				initial_error = 0;
				gd.set_learning_rate(0.01);
				auto errors = gd.get_errors(cluster, {0.1, 0.05});
				for(auto err : errors) {
					initial_error += err;
				}
				
				for(int i=0;i<1000;i++){
					gd(cluster, {0.1, 0.05});
					mul(cluster, {1.0,4.0,5.0});
				}
			});
			
			IT("should reduce the error in at least 10 times", {
				nerone::value_t error = 0;
				auto errors = gd.get_errors(cluster, {0.1, 0.05});
				for(auto err : errors) {
					error += err;
				}
				
				INFO_PRINT("initial error: " + std::to_string(initial_error));
				INFO_PRINT("error after trainings: " + std::to_string(error));
				
				EXPECT(error).toBeLessThan(initial_error/10.0);
			});
		});
	});
});

SCENARIO_END

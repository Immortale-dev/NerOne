#include <memory>

#include "ner_producer_gd.h"

SCENARIO_START

DESCRIBE("GDProducer", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	GDProducer<VT>* gd;
	
	DESCRIBE("empty instance is created", {
		BEFORE_EACH({
			gd = new GDProducer<VT>();
		});
		
		AFTER_EACH({
			delete gd;
		});
		
		IT("should set cell body", {
			auto c1 = std::make_shared<TestOCell<VT, 1, 2>>();
			auto c2 = std::make_shared<TestTCell<VT, 2, 2>>();
			auto c3 = std::make_shared<TestOCell<VT, 2, 1>>();
			auto cell = std::make_shared<cell::Layer<VT>>(nerone::cell_list_t{c1,c2,c3});
			
			gd->set_body_cell(cell);
			
			EXPECT(gd->get_body_cell()).toBe(cell);
		});
		
		IT("should set loss cell", {
			auto cell = std::make_shared<cell::LossLayer<VT>>(nerone::cell_list_t{});
			
			gd->set_loss_cell(cell);
			
			EXPECT(gd->get_loss_cell()).toBe(cell);
		});
	});
	
	DESCRIBE("instance with cells is created", {
		std::shared_ptr<cell::Layer<VT>> body;
		std::shared_ptr<cell::LossLayer<VT>> loss;
		BEFORE_EACH({
			body = std::make_shared<cell::Layer<VT>>(nerone::cell_list_t{});
			loss = std::make_shared<cell::LossLayer<VT>>(nerone::cell_list_t{});
			
			gd = new GDProducer<VT>(body, loss);
		});
		
		AFTER_EACH({
			delete gd;
		});
		
		IT("should return body cell", {
			EXPECT(gd->get_body_cell()).toBe(body);
		});
		
		IT("should return loss cell", {
			EXPECT(gd->get_loss_cell()).toBe(loss);
		});
		
		IT("should set learning rate", {
			gd->set_learning_rate(0.123);
			
			EXPECT(gd->get_learning_rate()).toBe(0.123);
		});
		
		IT("should set batch size", {
			gd->set_batch_size(14);
			
			EXPECT(gd->get_batch_size()).toBe(14);
		});
		
		IT("should set randomized", {
			gd->set_randomized(true);
			
			EXPECT(gd->get_randomized()).toBe(true);
		});
		
		IT("should set settings", {
			gd->apply_settings({0.234, 18, false});
			
			EXPECT(gd->get_learning_rate()).toBe(0.234);
			EXPECT(gd->get_batch_size()).toBe(18);
			EXPECT(gd->get_randomized()).toBe(false);
		});
	});
	
	DESCRIBE("produce is created and batch size of 1 is set", {
		BEFORE_EACH({
			gd = new GDProducer<VT>();
			gd->set_batch_size(1);			
		});
		
		DESCRIBE("instance 3->4->2 with biases is created", {
			auto test_fn = [](float val)->float{return val*2;};
			auto test_loss_fn = [](float v1, float v2)->float{return v2-v1;};
			BEFORE_EACH({
				ConnectedLayerBuilder b(true);
					b.add(3, nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>)
					.add(4, test_fn, test_fn)
					.add(2, test_fn, test_fn)
					.withLoss(test_loss_fn, test_loss_fn)
					.withWeights({
						{
							1.1, 1.2, -1.3, 0.15,
							1.5, -1.6, 1.7, 0.25,
							1.8, 1.9, 2.0, 0.35,
							2.1, 2.2, -2.3, 0.45
						},
						{
							0.55, 0.65, -0.75, 0.85, 0.5,
							-0.5, 0.1, 0.2, 0.3, 0.5
						}
					});
				auto [body, loss] = b.build();
				gd->set_body_cell(body);
				gd->set_loss_cell(loss);
			});
			
			IT("should calculated values correctly", {
				auto result = gd->execute({
					{
						{ //values
							0.3, 0.1, 0.2
						}
					}
				});
				auto result2 = gd->execute({
					{
						{ //values
							0.3, 0.1, 0.2
						}
					}
				});
				auto& exResult = result[0];
				auto& exResult2 = result2[0];
				auto expected = std::vector<float>{2.452, 2.864};
				
				EXPECT(result.size()).toBe(1);
				EXPECT(result2.size()).toBe(1);
				EXPECT(exResult.values.size()).toBe(2);
				EXPECT(exResult2.values.size()).toBe(2);
				for (size_t i=0;i<exResult.values.size();i++) {
					EXPECT(exResult.values[i]).toBeCloseTo(expected[i], 0.0001);
					EXPECT(exResult2.values[i]).toBeCloseTo(expected[i], 0.0001);
					INFO_PRINT() << exResult.values[i];
				}
				// values are cleaned.
				auto inputs = gd->get_body_cell()->get_inputs();
				for(auto inp : inputs) {
					EXPECT(std::static_pointer_cast<VT>(inp)->empty()).toBe(true);
				}
			});
			
			IT("should calculated values using partial execution", {
				gd->start_executing();
				auto result = gd->execute_partial({
					{
						{ //values
							0.3, 0.1, 0.2
						}
					},
					{
						{ //values
							0.3, 0.1, 0.2
						}
					}
				});
				auto result2 = gd->execute_partial({
					{
						{ //values
							0.3, 0.1, 0.2
						}
					}
				});
				gd->finish_executing();
				auto& exResult = result[0];
				auto& exResult2 = result2[0];
				auto& exResult3 = result[1];
				auto expected = std::vector<float>{2.452, 2.864};
				
				EXPECT(result.size()).toBe(2);
				EXPECT(result2.size()).toBe(1);
				EXPECT(exResult.values.size()).toBe(2);
				EXPECT(exResult2.values.size()).toBe(2);
				EXPECT(exResult3.values.size()).toBe(2);
				for (size_t i=0;i<exResult.values.size();i++) {
					EXPECT(exResult.values[i]).toBeCloseTo(expected[i], 0.0001);
					EXPECT(exResult2.values[i]).toBeCloseTo(expected[i], 0.0001);
					EXPECT(exResult3.values[i]).toBeCloseTo(expected[i], 0.0001);
					INFO_PRINT() << exResult.values[i];
				}
				// values are cleaned.
				auto inputs = gd->get_body_cell()->get_inputs();
				for(auto inp : inputs) {
					EXPECT(std::static_pointer_cast<VT>(inp)->empty()).toBe(true);
				}
			});
		});
		
		// DESCRIBE("instance 3->4->2 w/o biases is created", {
			// BEFORE_EACH({
				// gd = new GDProducer(body, loss);
			// });
			
			// AFTER_EACH({
				// delete gd;
			// });
			
			// IT("should calculated values correctly", {
				// // TODO
			// });
		// });
		
		// DESCRIBE("instance 3->2->2 with biases is created", {
			// BEFORE_EACH({
				// gd = new GDProducer(body, loss);
			// });
			
			// AFTER_EACH({
				// delete gd;
			// });
			
			// IT("should calculate values correctly", {
				// // TODO
			// });
			
			// IT("should calculate gradients correctly", {
				// // TODO
			// });
			
			// IT("should update weights correctly", {
				// // TODO
			// });
		// });
	});
});

SCENARIO_END

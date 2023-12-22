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
	
	DESCRIBE("produce is created", {
		BEFORE_EACH({
			gd = new GDProducer<VT>();
			gd->set_batch_size(1);			
		});
		
		AFTER_EACH({
			delete gd;
		});

		DESCRIBE("Batch size is set to 1", {
			BEFORE_EACH({
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
			
			DESCRIBE("instance 3->4->2 w/o biases is created", {
				auto test_fn = [](float val)->float{return val*2;};
				auto test_loss_fn = [](float v1, float v2)->float{return v2-v1;};
				
				BEFORE_EACH({
					ConnectedLayerBuilder b(false);
					b.add(3, nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>)
					.add(4, test_fn, test_fn)
					.add(2, test_fn, test_fn)
					.withLoss(test_loss_fn, test_loss_fn)
					.withWeights({
						{
							1.1, 1.2, -1.3,
							1.5, -1.6, 1.7,
							1.8, 1.9, 2.0,
							2.1, 2.2, -2.3
						},
						{
							0.55, 0.65, -0.75, 0.85,
							-0.5, 0.1, 0.2, 0.3
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
								0.5, 0.6, 0.7
							}
						},
						{
							{
								0.5, 0.6, 0.7
							},
							{
								2.0, 3.0,
							},
						}
					});
					auto expected = std::vector<float>{-4.396, 3.336};
					auto expectedErrors = std::vector<float>{6.396, -0.336};
					auto& res1 = result[0];
					auto& res2 = result[1];
					
					EXPECT(result.size()).toBe(2);
					EXPECT(res1.values.size()).toBe(2);
					EXPECT(res2.values.size()).toBe(2);
					EXPECT(res1.errors.size()).toBe(0);
					EXPECT(res2.errors.size()).toBe(2);
					for (size_t i=0;i<expected.size();i++) {
						EXPECT(res1.values[i]).toBeCloseTo(expected[i], 0.0001);
						EXPECT(res2.values[i]).toBeCloseTo(expected[i], 0.0001);
						EXPECT(res2.errors[i]).toBeCloseTo(expectedErrors[i], 0.0001);
						INFO_PRINT() << res1.values[i];
					}
				});
			});
			
			DESCRIBE("instance 3->2->2 with biases is created", {
				BEFORE_EACH({
					ConnectedLayerBuilder b(true);
					b.add(3, nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>)
					.add(2, nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>)
					.add(2, nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>)
					.withLoss(nerone::loss::MeanSquareError::fun<float>, nerone::loss::MeanSquareError::grad<float>)
					.withWeights({
						{
							0.1, 0.3, 0.5, 0.5,
							0.2, 0.4, 0.6, 0.5
						},
						{
							0.7, 0.9, 0.5,
							0.8, 0.1, 0.5
						}
					});
					auto [body, loss] = b.build();
					gd->set_body_cell(body);
					gd->set_loss_cell(loss);
				});
				
				IT("should calculate the result", {
					auto result = gd->execute({
						{
							{1.0, 4.0, 5.0}
						}
					});
					auto res = result[0];
					std::vector<float> expected{0.889551, 0.8004};
					
					EXPECT(res.values.size()).toBe(2);
					EXPECT(res.errors.size()).toBe(0);
					for(size_t i=0;i<res.values.size();i++) {
						EXPECT(res.values[i]).toBeCloseTo(expected[i], 0.00001);
					}
				});
				
				DESCRIBE("Learning rate is set to 0.01", {
					BEFORE_EACH({
						gd->set_learning_rate(0.01);
					});
					
					IT("should train the model and update weights", {
						gd->train({
							{
								{1.0, 4.0, 5.0},
								{0.1, 0.05}
							}
						});
						auto body = gd->get_body_cell();
						auto cells = body->get_cells();
						auto s1_w = std::static_pointer_cast<nerone::cell::Segment<VT>>(cells[1])->get_weights();
						auto s2_w = std::static_pointer_cast<nerone::cell::Segment<VT>>(cells[3])->get_weights();
						
						std::vector<float> s1_w_ex{
							0.0999802, 0.299921, 0.499901, 0.49998,
							0.199996, 0.399984, 0.59998, 0.499996
						};
						std::vector<float> s2_w_ex{
							0.699235, 0.899228, 0.499224,
							0.798817, 0.0988071, 0.498801
						};
						
						for(size_t i=0;i<s1_w.size();i++) {
							EXPECT(s1_w[i]).toBeCloseTo(s1_w_ex[i], 0.00001);
						}
						for(size_t i=0;i<s2_w.size();i++) {
							EXPECT(s2_w[i]).toBeCloseTo(s2_w_ex[i], 0.00001);
						}
					});
					
					IT("should reduce the error in at least 10 times", {
						auto res = gd->execute({{
							{1.0, 4.0, 5.0},
							{0.1, 0.05}
						}})[0];
						float initial_error = 0;
						for(float err : res.errors) {
							initial_error += err;
						}
						for(int i=0;i<1000;i++) {
							gd->train({
								{
									{1.0, 4.0, 5.0},
									{0.1, 0.05}
								}
							});
						}
						res = gd->execute({{
							{1.0, 4.0, 5.0},
							{0.1, 0.05}
						}})[0];
						float final_error = 0;
						for(float err : res.errors) {
							final_error += err;
						}
						EXPECT(final_error).toBeLessThan(initial_error/10.0);
						INFO_PRINT() << "Initial error: " << initial_error;
						INFO_PRINT() << "Final error: " << final_error;
					});
				});
			});
		});
		DESCRIBE("Batch size is set to 10, and learning rate to 0.01", {
			BEFORE_EACH({
				gd->set_batch_size(10);
				gd->set_learning_rate(0.01);
			});
			
			DESCRIBE("instance 3->2->2 with biases is created", {
				BEFORE_EACH({
					ConnectedLayerBuilder b(true);
					b.add(3, nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>)
					.add(2, nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>)
					.add(2, nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>)
					.withLoss(nerone::loss::MeanSquareError::fun<float>, nerone::loss::MeanSquareError::grad<float>)
					.withWeights({
						{
							0.1, 0.3, 0.5, 0.5,
							0.2, 0.4, 0.6, 0.5
						},
						{
							0.7, 0.9, 0.5,
							0.8, 0.1, 0.5
						}
					});
					auto [body, loss] = b.build();
					gd->set_body_cell(body);
					gd->set_loss_cell(loss);
				});
			
				IT("should reduce the error in at least 10 times", {
					auto res = gd->execute({{
						{1.0, 4.0, 5.0},
						{0.1, 0.05}
					}})[0];
					float initial_error = 0;
					for(float err : res.errors) {
						initial_error += err;
					}
					gd->start_training();
					for(int i=0;i<1000;i++) {
						gd->train_partial({
							{
								{1.0, 4.0, 5.0},
								{0.1, 0.05}
							}
						});
					}
					gd->finish_training();
					res = gd->execute({{
						{1.0, 4.0, 5.0},
						{0.1, 0.05}
					}})[0];
					float final_error = 0;
					for(float err : res.errors) {
						final_error += err;
					}
					EXPECT(final_error).toBeLessThan(initial_error/10.0);
					INFO_PRINT() << "Initial error: " << initial_error;
					INFO_PRINT() << "Final error: " << final_error;
				});
			});
		});
	});
});

SCENARIO_END

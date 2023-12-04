#include <memory>

#include "ner_cell_layer.h"
#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("cell::Layer", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::Layer<VT>> cell;
	
	DESCRIBE("cell is constructed", {
		std::shared_ptr<TestOCell<VT, 1, 2>> c1;
		std::shared_ptr<TestTCell<VT, 2, 2>> c2;
		std::shared_ptr<TestOCell<VT, 2, 1>> c3;
		
		BEFORE_EACH({
			c1 = std::make_shared<TestOCell<VT, 1, 2>>();
			c2 = std::make_shared<TestTCell<VT, 2, 2>>();
			c3 = std::make_shared<TestOCell<VT, 2, 1>>();
			cell = std::make_shared<cell::Layer<VT>>(nerone::cell_list_t{c1,c2,c3});
		});
		
		IT("should correctly return inputs and outputs", {
			value_list_t combined_inputs{c1->get_inputs()[0], c2->get_inputs()[0], c2->get_inputs()[1], c3->get_inputs()[0], c3->get_inputs()[1]};
			value_list_t combined_outputs{c1->get_outputs()[0], c1->get_outputs()[1], c2->get_outputs()[0], c2->get_outputs()[1], c3->get_outputs()[0]};
			
			EXPECT(cell->get_inputs().size()).toBe(5);
			EXPECT(cell->get_outputs().size()).toBe(5);
			for(size_t i=0;i<combined_inputs.size();i++) {
				EXPECT(cell->get_inputs()[i]).toBe(combined_inputs[i]);
			}
			for(size_t i=0;i<combined_outputs.size();i++) {
				EXPECT(cell->get_outputs()[i]).toBe(combined_outputs[i]);
			}
		});
		
		IT("should properly call calc_value function", {
			int i=0;
			for(auto it : cell->get_inputs()) {
				std::static_pointer_cast<VT>(it)->set(float(++i));
			}
			
			cell->calc_value();
			
			std::vector<float> outputs{1.0, 2.0, 5.0, 10.0, 9.0};
			for(size_t i=0;i<outputs.size();i++) {
				EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[i])->get()).toBeCloseTo(outputs[i], 0.001);
			}
		});
		
		IT("should properly call calc_grad function", {
			int i=0;
			for(auto it : cell->get_inputs()) {
				std::static_pointer_cast<VT>(it)->set(float(++i));
			}
			cell->calc_value();
			i=1;
			for(auto it : cell->get_outputs()) {
				std::static_pointer_cast<VT>(it)->set_grad(float(++i));
			}
			cell->calc_grad();
			
			std::vector<float> grads{10.0, 18.0, 27.0, 12.0, 18.0};
			for(size_t i=0;i<grads.size();i++) {
				EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[i])->get_grad()).toBeCloseTo(grads[i], 0.001);
			}
		});
		
		IT("should call update for a trainable cell", {
			cell->update({});
			
			EXPECT(c2->get_updated_times()).toBe(1);
		});
		
		DESCRIBE("cells are reassigned", {
			std::shared_ptr<TestOCell<VT, 2, 2>> c22;
			
			BEFORE_EACH({
				c22 = std::make_shared<TestOCell<VT, 2, 2>>();
				
				cell->set_cells(nerone::cell_list_t{c1,c22,c3});
			});
			
			IT("should use new inputs and outputs", {
				value_list_t combined_inputs{c1->get_inputs()[0], c22->get_inputs()[0], c22->get_inputs()[1], c3->get_inputs()[0], c3->get_inputs()[1]};
				value_list_t combined_outputs{c1->get_outputs()[0], c1->get_outputs()[1], c22->get_outputs()[0], c22->get_outputs()[1], c3->get_outputs()[0]};
				
				EXPECT(cell->get_inputs().size()).toBe(5);
				EXPECT(cell->get_outputs().size()).toBe(5);
				for(size_t i=0;i<combined_inputs.size();i++) {
					EXPECT(cell->get_inputs()[i]).toBe(combined_inputs[i]);
				}
				for(size_t i=0;i<combined_outputs.size();i++) {
					EXPECT(cell->get_outputs()[i]).toBe(combined_outputs[i]);
				}
			});
			
			IT("should calculate values and grads correctly", {
				int i=0;
				for(auto it : cell->get_inputs()) {
					std::static_pointer_cast<VT>(it)->set(float(++i));
				}
				cell->calc_value();
				i=1;
				for(auto it : cell->get_outputs()) {
					std::static_pointer_cast<VT>(it)->set_grad(float(++i));
				}
				cell->calc_grad();
				
				std::vector<float> outputs{1.0, 2.0, 5.0, 10.0, 9.0};
				for(size_t i=0;i<outputs.size();i++) {
					EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[i])->get()).toBeCloseTo(outputs[i], 0.001);
				}
				std::vector<float> grads{10.0, 18.0, 27.0, 12.0, 18.0};
				for(size_t i=0;i<grads.size();i++) {
					EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[i])->get_grad()).toBeCloseTo(grads[i], 0.001);
				}
			});
			
			IT("should clean values", {
				std::static_pointer_cast<VT>(c1->get_inputs()[0])->set(1);
				
				cell->clean();
				
				EXPECT(std::static_pointer_cast<VT>(c1->get_inputs()[0])->empty()).toBe(true);
			});
		});
		
		DESCRIBE("inputs are reassigned", {
			value_list_t new_inputs, new_outputs;
			
			BEFORE_EACH({
				for(int i=0;i<5;i++) {
					new_inputs.push_back(std::make_shared<VT>());
					new_outputs.push_back(std::make_shared<VT>());
				}
				cell->set_inputs(new_inputs);
				cell->set_outputs(new_outputs);
			});
			
			IT("should reassign values correctly", {
				value_list_t combined_inputs{c1->get_inputs()[0], c2->get_inputs()[0], c2->get_inputs()[1], c3->get_inputs()[0], c3->get_inputs()[1]};
				value_list_t combined_outputs{c1->get_outputs()[0], c1->get_outputs()[1], c2->get_outputs()[0], c2->get_outputs()[1], c3->get_outputs()[0]};
				
				for(size_t i=0;i<new_inputs.size();i++) {
					EXPECT(cell->get_inputs()[i]).toBe(new_inputs[i]);
					EXPECT(cell->get_outputs()[i]).toBe(new_outputs[i]);
					// EXPECT(cell->get_inputs()[i]).toBe(combined_inputs[i]);
					// EXPECT(cell->get_outputs()[i]).toBe(combined_outputs[i]);
				}
			});
			
			IT("should still work correctly", {
				int i=0;
				for(auto it : cell->get_inputs()) {
					std::static_pointer_cast<VT>(it)->set(float(++i));
				}
				cell->calc_value();
				i=1;
				for(auto it : cell->get_outputs()) {
					std::static_pointer_cast<VT>(it)->set_grad(float(++i));
				}
				cell->calc_grad();
				
				std::vector<float> outputs{1.0, 2.0, 5.0, 10.0, 9.0};
				for(size_t i=0;i<outputs.size();i++) {
					EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[i])->get()).toBeCloseTo(outputs[i], 0.001);
				}
				std::vector<float> grads{10.0, 18.0, 27.0, 12.0, 18.0};
				for(size_t i=0;i<grads.size();i++) {
					EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[i])->get_grad()).toBeCloseTo(grads[i], 0.001);
				}
			});
		});
	});
});

SCENARIO_END

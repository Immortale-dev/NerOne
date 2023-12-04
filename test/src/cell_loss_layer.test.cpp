#include <memory>

#include "ner_cell_layer.h"
#include "ner_value_cu.h"

auto l_fn = [](float a, float e)->float{ return a-e; };
auto l_gd = [](float a, float e)->float{ return (a-e)*0.5; };

SCENARIO_START

DESCRIBE("cell::LossLayer", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::LossLayer<VT>> cell;
	
	DESCRIBE("cell is constructed", {
		std::shared_ptr<cell::Loss<VT>> c1, c2, c3;
		
		BEFORE_EACH({
			c1 = std::make_shared<cell::Loss<VT>>(l_fn, l_gd);
			c2 = std::make_shared<cell::Loss<VT>>(l_fn, l_gd);
			c3 = std::make_shared<cell::Loss<VT>>(l_fn, l_gd);
			cell = std::make_shared<cell::LossLayer<VT>>(nerone::cell_list_t{c1,c2,c3});
		});
		
		IT("should correctly return inputs and outputs", {
			value_list_t combined_inputs{c1->get_inputs()[0], c2->get_inputs()[0], c3->get_inputs()[0]};
			value_list_t combined_outputs{c1->get_outputs()[0], c2->get_outputs()[0], c3->get_outputs()[0]};
			
			EXPECT(cell->get_inputs().size()).toBe(3);
			EXPECT(cell->get_outputs().size()).toBe(3);
			for(size_t i=0;i<combined_inputs.size();i++) {
				EXPECT(cell->get_inputs()[i]).toBe(combined_inputs[i]);
			}
			for(size_t i=0;i<combined_outputs.size();i++) {
				EXPECT(cell->get_outputs()[i]).toBe(combined_outputs[i]);
			}
		});
		
		IT("should return expected inputs", {
			auto vals = cell->get_expected_inputs();
			
			EXPECT(vals.size()).toBe(3);
		});
		
		IT("should properly call calc_value function", {
			int i=0;
			for(auto it : cell->get_inputs()) {
				std::static_pointer_cast<VT>(cell->get_expected_inputs()[i])->set(4-i);
				std::static_pointer_cast<VT>(it)->set(float(++i));
			}
			
			cell->calc_value();
			
			std::vector<float> outputs{-3.0, -1.0, 1.0};
			for(size_t i=0;i<outputs.size();i++) {
				EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[i])->get()).toBeCloseTo(outputs[i], 0.001);
			}
		});
		
		IT("should properly call calc_grad function", {
			int i=0;
			for(auto it : cell->get_inputs()) {
				std::static_pointer_cast<VT>(cell->get_expected_inputs()[i])->set(4-i);
				std::static_pointer_cast<VT>(it)->set(float(++i));
			}
			
			cell->calc_value();
			cell->calc_grad();
			
			std::vector<float> grads{-1.5, -0.5, 0.5};
			for(size_t i=0;i<grads.size();i++) {
				EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[i])->get_grad()).toBeCloseTo(grads[i], 0.001);
			}
		});
		
		DESCRIBE("cells are reassigned", {
			std::shared_ptr<cell::Loss<VT>> c22;
			value_list_t new_expected;
			
			BEFORE_EACH({
				c22 = std::make_shared<cell::Loss<VT>>(l_fn, l_gd);
				for(int i=0;i<3;i++) {
					new_expected.push_back(std::make_shared<VT>());
				}
				cell->set_cells(nerone::cell_list_t{c1,c22,c3});
				cell->set_expected_inputs(new_expected);
			});
			
			IT("should use new inputs and outputs", {
				value_list_t combined_inputs{c1->get_inputs()[0], c22->get_inputs()[0], c3->get_inputs()[0]};
				value_list_t combined_outputs{c1->get_outputs()[0], c22->get_outputs()[0], c3->get_outputs()[0]};
			
				EXPECT(cell->get_inputs().size()).toBe(3);
				EXPECT(cell->get_outputs().size()).toBe(3);
				EXPECT(cell->get_expected_inputs().size()).toBe(3);
				for(size_t i=0;i<combined_inputs.size();i++) {
					EXPECT(cell->get_inputs()[i]).toBe(combined_inputs[i]);
				}
				for(size_t i=0;i<combined_outputs.size();i++) {
					EXPECT(cell->get_outputs()[i]).toBe(combined_outputs[i]);
				}
				for(size_t i=0;i<new_expected.size();i++) {
					EXPECT(cell->get_expected_inputs()[i]).toBe(new_expected[i]);
				}
			});
			
			IT("should calculate values and grads correctly", {
				int i=0;
				for(auto it : cell->get_inputs()) {
					std::static_pointer_cast<VT>(new_expected[i])->set(4-i);
					std::static_pointer_cast<VT>(it)->set(float(++i));
				}
				
				cell->calc_value();
				cell->calc_grad();
				
				std::vector<float> outputs{-3.0, -1.0, 1.0};
				for(size_t i=0;i<outputs.size();i++) {
					EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[i])->get()).toBeCloseTo(outputs[i], 0.001);
				}
				std::vector<float> grads{-1.5, -0.5, 0.5};
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
	});
});

SCENARIO_END

#include <memory>

#include "ner_cell_seg.h"
#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("cell::Segment", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::Segment<VT>> cell;
	
	DESCRIBE("cell is default constructed", {
		BEFORE_EACH({
			cell = std::make_shared<cell::Segment<VT>>();
		});
		
		IT("should return empty lists", {
			EXPECT(cell->get_inputs().size()).toBe(0);
			EXPECT(cell->get_outputs().size()).toBe(0);
			EXPECT(cell->get_weights().size()).toBe(0);
		});
		
		IT("should not do anything", {
			cell->calc_value();
			cell->calc_grad();
			
			EXPECT(cell->get_outputs().size()).toBe(0);
		});
		
		DESCRIBE("inputs and outputs are assigned", {
			std::vector<std::shared_ptr<VT>> inputs;
			std::vector<std::shared_ptr<VT>> outputs;
			
			BEFORE_EACH({
				inputs.resize(0);
				outputs.resize(0);
				for(int i=0;i<3;i++) {
					inputs.push_back(std::make_shared<VT>());
				}
				for(int i=0;i<2;i++) {
					outputs.push_back(std::make_shared<VT>());
				}
				cell->set_inputs(nerone::value_list_t(inputs.begin(), inputs.end()));
				cell->set_outputs(nerone::value_list_t(outputs.begin(), outputs.end()));
			});
			
			IT("weights should be defined", {
				EXPECT(cell->get_inputs().size()).toBe(3);
				EXPECT(cell->get_outputs().size()).toBe(2);
				EXPECT(cell->get_weights().size()).toBe(6);
			});
		});
	});
	
	DESCRIBE("cell is constructed", {
		std::vector<std::shared_ptr<VT>> inputs;
		std::vector<std::shared_ptr<VT>> outputs;
		
		BEFORE_EACH({
			inputs.resize(0);
			outputs.resize(0);
			for(int i=0;i<3;i++) {
				inputs.push_back(std::make_shared<VT>());
			}
			for(int i=0;i<2;i++) {
				outputs.push_back(std::make_shared<VT>());
			}
			cell = std::make_shared<cell::Segment<VT>>(nerone::value_list_t(inputs.begin(), inputs.end()), nerone::value_list_t(outputs.begin(), outputs.end()));
			cell->set_weights(std::vector<float>{0.1, 0.2, 0.3, 0.4, 0.5, 0.6});
		});
		
		IT("weights should be defined", {
			EXPECT(cell->get_weights().size()).toBe(6);
		});
		
		IT("should calculate output values", {
			inputs[0]->set(1.2);
			inputs[1]->set(1.3);
			inputs[2]->set(1.4);
			
			cell->calc_value();
			
			INFO_PRINT() << "Outputs: " << outputs[0]->get() << " " << outputs[1]->get();
			
			EXPECT(outputs[0]->get()).toBeCloseTo(1.2 * 0.1 + 1.3 * 0.2 + 1.4 * 0.3, 0.001);
			EXPECT(outputs[1]->get()).toBeCloseTo(1.2 * 0.4 + 1.3 * 0.5 + 1.4 * 0.6, 0.001);
		});
		
		IT("should calculate output values", {
			inputs[0]->set(1.2);
			inputs[1]->set(1.3);
			inputs[2]->set(1.4);
			
			cell->calc_value();
			
			outputs[0]->set_grad(2.2);
			outputs[1]->set_grad(2.8);
			
			cell->calc_grad();
			
			INFO_PRINT() << "Grads: " << inputs[0]->get_grad() << " " << inputs[1]->get_grad() << " " << inputs[2]->get_grad();
			
			EXPECT(inputs[0]->get_grad()).toBeCloseTo(2.2 * 0.1 + 2.8 * 0.4, 0.001);
			EXPECT(inputs[1]->get_grad()).toBeCloseTo(2.2 * 0.2 + 2.8 * 0.5, 0.001);
			EXPECT(inputs[2]->get_grad()).toBeCloseTo(2.2 * 0.3 + 2.8 * 0.6, 0.001);
		});
		
		IT("should update weights in respect to multiple queued gradient calls", {
			// call 1
			inputs[0]->set(1.2);
			inputs[1]->set(1.3);
			inputs[2]->set(1.4);
			cell->calc_value();
			outputs[0]->set_grad(2.2);
			outputs[1]->set_grad(2.8);
			cell->calc_grad();
			
			// call 2
			inputs[0]->set(2.2);
			inputs[1]->set(2.3);
			inputs[2]->set(2.4);
			cell->calc_value();
			outputs[0]->set_grad(2.3);
			outputs[1]->set_grad(2.9);
			cell->calc_grad();
			
			//call 3
			inputs[0]->set(3.2);
			inputs[1]->set(3.3);
			inputs[2]->set(3.4);
			cell->calc_value();
			outputs[0]->set_grad(2.5);
			outputs[1]->set_grad(2.7);
			cell->calc_grad();
			
			cell->update(std::make_shared<GDTrainData>(-0.1));
			
			std::vector<float> wghts{
				0.1 - 0.1 * (2.2 * 1.2 + 2.3 * 2.2 + 2.5 * 3.2),
				0.2 - 0.1 * (2.2 * 1.3 + 2.3 * 2.3 + 2.5 * 3.3),
				0.3 - 0.1 * (2.2 * 1.4 + 2.3 * 2.4 + 2.5 * 3.4),
				0.4 - 0.1 * (2.8 * 1.2 + 2.9 * 2.2 + 2.7 * 3.2),
				0.5 - 0.1 * (2.8 * 1.3 + 2.9 * 2.3 + 2.7 * 3.3),
				0.6 - 0.1 * (2.8 * 1.4 + 2.9 * 2.4 + 2.7 * 3.4)
			};
			
			for(size_t i=0;i<wghts.size();i++) {
				EXPECT(cell->get_weights()[i]).toBeCloseTo(wghts[i], 0.001);
			}
		});
		
		IT("should update weights in respect to multiple stacked gradient calls", {
			// call 1
			inputs[0]->set(1.2);
			inputs[1]->set(1.3);
			inputs[2]->set(1.4);
			cell->calc_value();
			
			// call 2
			inputs[0]->set(2.2);
			inputs[1]->set(2.3);
			inputs[2]->set(2.4);
			cell->calc_value();
			
			//call 3
			inputs[0]->set(3.2);
			inputs[1]->set(3.3);
			inputs[2]->set(3.4);
			cell->calc_value();
			
			//grads
			outputs[0]->set_grad(2.5);
			outputs[1]->set_grad(2.7);
			cell->calc_grad();
			outputs[0]->set_grad(2.3);
			outputs[1]->set_grad(2.9);
			cell->calc_grad();
			outputs[0]->set_grad(2.2);
			outputs[1]->set_grad(2.8);
			cell->calc_grad();
			
			cell->update(std::make_shared<GDTrainData>(-0.1));
			
			std::vector<float> wghts{
				0.1 - 0.1 * (2.2 * 1.2 + 2.3 * 2.2 + 2.5 * 3.2),
				0.2 - 0.1 * (2.2 * 1.3 + 2.3 * 2.3 + 2.5 * 3.3),
				0.3 - 0.1 * (2.2 * 1.4 + 2.3 * 2.4 + 2.5 * 3.4),
				0.4 - 0.1 * (2.8 * 1.2 + 2.9 * 2.2 + 2.7 * 3.2),
				0.5 - 0.1 * (2.8 * 1.3 + 2.9 * 2.3 + 2.7 * 3.3),
				0.6 - 0.1 * (2.8 * 1.4 + 2.9 * 2.4 + 2.7 * 3.4)
			};
			
			for(size_t i=0;i<wghts.size();i++) {
				EXPECT(cell->get_weights()[i]).toBeCloseTo(wghts[i], 0.001);
			}
		});
		
		IT("should clean up after each update", {
			// call 1
			inputs[0]->set(1.2);
			inputs[1]->set(1.3);
			inputs[2]->set(1.4);
			cell->calc_value();
			outputs[0]->set_grad(2.2);
			outputs[1]->set_grad(2.8);
			cell->calc_grad();
			cell->update(std::make_shared<GDTrainData>(-0.1));
			
			std::vector<float> wghts = cell->get_weights();
			
			// call 2
			inputs[0]->set(2.2);
			inputs[1]->set(2.3);
			inputs[2]->set(2.4);
			cell->calc_value();
			outputs[0]->set_grad(2.3);
			outputs[1]->set_grad(2.9);
			cell->calc_grad();
			cell->update(std::make_shared<GDTrainData>(-0.1));
			
			// TODO: weights are updated, change second part of eq.
			std::vector<double> new_wghts{
				wghts[0] - 0.1 * (2.3 * 2.2),
				wghts[1] - 0.1 * (2.3 * 2.3),
				wghts[2] - 0.1 * (2.3 * 2.4),
				wghts[3] - 0.1 * (2.9 * 2.2),
				wghts[4] - 0.1 * (2.9 * 2.3),
				wghts[5] - 0.1 * (2.9 * 2.4)
			};
			
			for(size_t i=0;i<wghts.size();i++) {
				EXPECT(cell->get_weights()[i]).toBeCloseTo(new_wghts[i], 0.001);
			}
		});
	});
});

SCENARIO_END

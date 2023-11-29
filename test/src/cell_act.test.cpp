#include <memory>

#include "ner_cell_act.h"
#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("cell::Activation", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::Activation<VT>> cell;
	
	DESCRIBE("default constructed cell", {
		BEFORE_EACH({
			cell = std::make_shared<cell::Activation<VT>>();
		});
		
		IT("should have 1 input and 1 output", {
			EXPECT(cell->get_inputs().size()).toBe(1);
			EXPECT(cell->get_outputs().size()).toBe(1);
		});
		
		IT("should apply linear activation function to input cell and write result into output cell", {
			std::static_pointer_cast<VT>(cell->get_inputs()[0])->set(1.5);
			cell->calc_value();
			
			EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[0])->get()).toBe(1.5);
		});
		
		IT("should apply linear activation function gradiend to the output gradient value and write result to input cell", {
			std::static_pointer_cast<VT>(cell->get_outputs()[0])->set_grad(3.2);
			cell->calc_grad();
			
			EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[0])->get_grad()).toBe(3.2);
		});
		
		DESCRIBE("change activation and functions", {
			BEFORE_EACH({
				cell->set_act_fn([](float a)->float{ return a*2.0; });
				cell->set_grad_fn([](float a)->float{ return a*3.0; });
			});
			
			IT("should use new functions", {
				std::static_pointer_cast<VT>(cell->get_inputs()[0])->set(2.2);
				cell->calc_value();
				std::static_pointer_cast<VT>(cell->get_outputs()[0])->set_grad(1.2);
				cell->calc_grad();

				EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[0])->get()).toBeCloseTo(4.4, 0.001);
				EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[0])->get_grad()).toBeCloseTo(1.2*6.6, 0.001);
			});
		});
	});
	
	DESCRIBE("funcionally constructed cell", {
		BEFORE_EACH({
			cell = std::make_shared<cell::Activation<VT>>([](float a)->float{ return a*2.0; }, [](float a)->float{ return a*3.0; });
		});
		
		IT("should use assigned functions", {
			std::static_pointer_cast<VT>(cell->get_inputs()[0])->set(2.2);
			cell->calc_value();
			std::static_pointer_cast<VT>(cell->get_outputs()[0])->set_grad(1.2);
			cell->calc_grad();

			EXPECT(std::static_pointer_cast<VT>(cell->get_outputs()[0])->get()).toBeCloseTo(4.4, 0.001);
			EXPECT(std::static_pointer_cast<VT>(cell->get_inputs()[0])->get_grad()).toBeCloseTo(1.2*6.6, 0.001);
		});
		
		DESCRIBE("new inputs and outputs assigned", {
			std::shared_ptr<VT> input_v, output_v;
			
			BEFORE_EACH({
				input_v = std::make_shared<VT>();
				output_v = std::make_shared<VT>();
				
				cell->set_inputs({input_v});
				cell->set_outputs({output_v});
			});
			
			IT("should use newly assigned values", {
				input_v->set(1.4);
				cell->calc_value();
				output_v->set_grad(2.1);
				cell->calc_grad();
				
				EXPECT(input_v).toBe(std::static_pointer_cast<VT>(cell->get_inputs()[0]));
				EXPECT(output_v).toBe(std::static_pointer_cast<VT>(cell->get_outputs()[0]));
				EXPECT(output_v->get()).toBeCloseTo(2.8, 0.001);
				EXPECT(input_v->get_grad()).toBeCloseTo(2.1 * 4.2, 0.001);
			});
		});
	});
});

SCENARIO_END

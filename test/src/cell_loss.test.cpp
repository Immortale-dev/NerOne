#include <memory>

#include "ner_cell_loss.h"
#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("cell::Loss", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::Loss<VT>> cell;
	
	DESCRIBE("constructed cell", {
		std::shared_ptr<VT> input_v, output_v;
		
		BEFORE_EACH({
			input_v = std::make_shared<VT>();
			output_v = std::make_shared<VT>();
			
			cell = std::make_shared<cell::Loss<VT>>(input_v, output_v, [](float a, float e)->float{ return a-e; }, [](float a, float e)->float{ return (a-e)*0.5; });
		});
		
		IT("should have 1 input and 1 output", {
			EXPECT(cell->get_inputs().size()).toBe(1);
			EXPECT(cell->get_outputs().size()).toBe(1);
		});
		
		IT("should calculate loss function", {
			input_v->set(4.0);
			cell->calc_value(5.0);
			cell->calc_grad();
			
			EXPECT(output_v->get()).toBeCloseTo(-1.0, 0.001);
			EXPECT(input_v->get_grad()).toBeCloseTo(-0.5, 0.001);
		});
		
		DESCRIBE("set new expected value", {
			std::shared_ptr<VT> expected_v;
			
			BEFORE_EACH({
				expected_v = std::make_shared<VT>();
				cell->set_expected_value(expected_v);
			});
			
			IT("should also calculate loss function", {
				input_v->set(3.0);
				expected_v->set(7.0);
				cell->calc_value();
				cell->calc_grad();

				EXPECT(output_v->get()).toBeCloseTo(-4.0, 0.001);
				EXPECT(input_v->get_grad()).toBeCloseTo(-2.0, 0.001);
			});
			
			IT("should clean values", {
				input_v->set(3.0);
				input_v->set(4.0);
				input_v->set(5.0);
				
				output_v->set(4.0);
				output_v->set(5.0);
				output_v->set(6.0);
				
				expected_v->set(5.0);
				expected_v->set(6.0);
				expected_v->set(7.0);
				
				cell->clean();
				
				EXPECT(input_v->empty()).toBe(true);
				EXPECT(output_v->empty()).toBe(true);
				EXPECT(expected_v->empty()).toBe(true);
			});
		});
	});
});

SCENARIO_END

#include <memory>

#include "ner_cell_seq.h"
#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("cell::Sequence", {
	using namespace nerone;
	using VT = value::Cumulative<float>;
	
	std::shared_ptr<cell::Sequence<VT>> cell;
	
	DESCRIBE("cell is constructed", {
		std::shared_ptr<TestOCell<VT, 1, 2>> c1;
		std::shared_ptr<TestTCell<VT, 2, 2>> c2;
		std::shared_ptr<TestOCell<VT, 2, 1>> c3;
		
		BEFORE_EACH({
			c1 = std::make_shared<TestOCell<VT, 1, 2>>();
			c2 = std::make_shared<TestTCell<VT, 2, 2>>();
			c3 = std::make_shared<TestOCell<VT, 2, 1>>();
			cell = std::make_shared<cell::Sequence<VT>>(nerone::cell_list_t{c1,c2,c3});
			cell->connect_cells();
		});
		
		IT("should reassign cell inputs and outputs so they are all connected", {
			for(size_t i=0;i<c1->get_outputs().size();i++) {
				EXPECT(c1->get_outputs()[i]).toBe(c2->get_inputs()[i]);
			}
			for(size_t i=0;i<c2->get_outputs().size();i++) {
				EXPECT(c2->get_outputs()[i]).toBe(c3->get_inputs()[i]);
			}
		});
		
		IT("should properly call calc_value function", {
			std::static_pointer_cast<VT>(c1->get_inputs()[0])->set(1);
			cell->calc_value();
			auto outputs = c3->get_outputs();
			
			EXPECT(std::static_pointer_cast<VT>(outputs[0])->get()).toBeCloseTo(9.0, 0.001);
		});
		
		IT("should properly call calc_grad function", {
			std::static_pointer_cast<VT>(c1->get_inputs()[0])->set(1);
			cell->calc_value();
			std::static_pointer_cast<VT>(c3->get_outputs()[0])->set_grad(1.5);
			cell->calc_grad();
			
			INFO_PRINT() << "Grad: " << std::static_pointer_cast<VT>(c1->get_inputs()[0])->get_grad();
			
			EXPECT(std::static_pointer_cast<VT>(c1->get_inputs()[0])->get_grad()).toBeCloseTo(75.0, 0.001);
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
				cell->connect_cells();
			});
			
			IT("should calculate values and grads correctly", {
				std::static_pointer_cast<VT>(c1->get_inputs()[0])->set(1);
				cell->calc_value();
				std::static_pointer_cast<VT>(c3->get_outputs()[0])->set_grad(1.5);
				cell->calc_grad();
				
				INFO_PRINT() << "Value: " << std::static_pointer_cast<VT>(c3->get_outputs()[0])->get();
				INFO_PRINT() << "Grad: " << std::static_pointer_cast<VT>(c1->get_inputs()[0])->get_grad();
				
				EXPECT(std::static_pointer_cast<VT>(c3->get_outputs()[0])->get()).toBeCloseTo(9.0, 0.001);
				EXPECT(std::static_pointer_cast<VT>(c1->get_inputs()[0])->get_grad()).toBeCloseTo(75.0, 0.001);
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

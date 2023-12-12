#include <memory>

#include "ner_value_cu_bias.h"

SCENARIO_START

DESCRIBE("value::CumulativeBias", {
	using namespace nerone;
	
	std::shared_ptr<value::CumulativeBias<float>> val;
	
	BEFORE_EACH({
		val = std::make_shared<value::CumulativeBias<float>>();
	});
	
	DESCRIBE("value is set", {
		IT("should return `1` by default", {
			EXPECT(val->get()).toBeCloseTo(1.0, 0.001);
		});
		
		DESCRIBE("set value to be `2`", {
			BEFORE_EACH({
				val->set(2.0);
			});
			
			IT("should return `2`", {
				EXPECT(val->get()).toBeCloseTo(2.0, 0.001);
			});
			
			IT("should still return `2` after grad is set", {
				val->set_grad(3.0);
				val->set_grad(4.0);
				val->set_grad(2.0);
				
				EXPECT(val->get()).toBeCloseTo(2.0, 0.001);
			});
			
			IT("should return `0` when get_grad is called", {
				val->set_grad(11.1);
				
				EXPECT(val->get_grad()).toBe(0);
			});
		});
		
		IT("should return false when empty is called", {
			EXPECT(val->empty()).toBe(false);
			
			val->clean();
			
			EXPECT(val->empty()).toBe(false);
		});
	});
});

SCENARIO_END

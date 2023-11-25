#include <memory>

#include "ner_value_cu.h"

SCENARIO_START

DESCRIBE("value::Cumulative", {
	using namespace nerone;
	
	std::shared_ptr<value::Cumulative<float>> val;
	
	BEFORE_EACH({
		val = std::make_shared<value::Cumulative<float>>();
	});
	
	DESCRIBE("value is set", {
		BEFORE_EACH({
			val->set(12.5);
		});
		
		IT("should return correct value", {
			EXPECT(val->get()).toBe(12.5);
			EXPECT(val->empty()).toBe(false);
		});
		IT("should still return its top value", {
			val->set_grad(0.5);
			val->set_grad(0.4);
			val->set_grad(0.3);
			
			EXPECT(val->get()).toBe(12.5);
			EXPECT(val->get_grad()).toBe(0.3);
			EXPECT(val->empty()).toBe(true);
		});
	});
	
	DESCRIBE("multiple values are set", {
		BEFORE_EACH({
			val->set(1);
			val->set(2);
			val->set(3);
		});
		
		IT("should return the latest set value", {
			EXPECT(val->get()).toBe(3);
			EXPECT(val->empty()).toBe(false);
		});
		IT("should return previously set value", {
			val->set_grad(0.5);
			
			EXPECT(val->get()).toBe(2);
			EXPECT(val->get_grad()).toBe(0.5);
			EXPECT(val->empty()).toBe(false);
		});
		IT("should return first value", {
			val->set_grad(0.5);
			val->set_grad(0.4);
			
			EXPECT(val->get()).toBe(1);
			EXPECT(val->get_grad()).toBe(0.4);
			EXPECT(val->empty()).toBe(false);
		});
		IT("should return second value", {
			val->pop();
			
			EXPECT(val->get()).toBe(2);
			EXPECT(val->empty()).toBe(false);
		});
		IT("should still return first value", {
			val->set_grad(0.3);
			val->set_grad(0.2);
			val->pop();
			val->pop();
			val->pop();
			
			EXPECT(val->get()).toBe(1);
			EXPECT(val->empty()).toBe(true);
			EXPECT(val->get_grad()).toBe(0.2);
		});
		IT("should return second value", {
			val->set_grad(0.1);
			val->clear();
			
			EXPECT(val->get()).toBe(2);
			EXPECT(val->empty()).toBe(true);
			EXPECT(val->get_grad()).toBe(0.1);
		});
		IT("should still return second value", {
			val->set_grad(0.1);
			val->clear();
			val->pop();
			
			EXPECT(val->get()).toBe(2);
			EXPECT(val->empty()).toBe(true);
			EXPECT(val->get_grad()).toBe(0.1);
		});
	});
});

SCENARIO_END

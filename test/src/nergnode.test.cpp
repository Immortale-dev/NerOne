SCENARIO_START

DESCRIBE("GNode", {
	nerone::GNode* node;
	
	DESCRIBE("Initialize instance with acnt and gradient functions", {
		BEFORE_EACH({
			node = new nerone::GNode(0.3, [](auto val){return val*2;}, [](auto val){return val*3;});
		});
		AFTER_EACH({
			delete node;
		});
		
		IT("should return 2 when activation function is called with value=1", {
			EXPECT(node->get_act_fn()(1)).toBe(2);
		});
		
		IT("should return 3 when gradient function is called with value=1", {
			EXPECT(node->get_gradient_fn()(1)).toBe(3);
		});
	});
	
	DESCRIBE("Initialize default constructor instance", {
		BEFORE_EACH({
			node = new nerone::GNode();
		});
		AFTER_EACH({
			delete node;
		});
		
		DESCRIBE("Set gradient function", {
			BEFORE_EACH({
				node->set_gradient_fn([](nerone::value_t a){return a*5;});
			});
			
			IT("shuld return `7.5` when gradient function is called with value=1.5", {
				EXPECT(node->get_gradient_fn()(1.5)).toBe(7.5);
			});
		});
	});
});

SCENARIO_END

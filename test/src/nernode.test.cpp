DESCRIBE("NerNode", {
	nerone::NerNode* node;
	
	DESCRIBE("initialize default constructor instance", {
		BEFORE_EACH({
			node = new nerone::NerNode();
		});
		AFTER_EACH({
			delete node;
		});
		
		IT("should succeed", {
			EXPECT(node->get_syns()).toBe({});
		});
		
		IT("setting value with `set_value` should return this value with `get_value`", {
			node->set_value(123.45);
			
			EXPECT(node->get_value()).toBe(123.45);
		});
		
		IT("setting syns with `set_syns` should return this list with `get_syns`", {
			node->set_syns({ std::make_shared<nerone::NerSyn>() });
			
			EXPECT(node->get_syns().size()).toBe(1);
		});
		
		IT("setting act fn with `set_act_fn` should return it with get_act_fn", {
			node->set_act_fn([](nerone::value_t a){ return a*2; });
			
			EXPECT(node->get_act_fn()(1.1)).toBe(2.2);
		});
	});
	
	DESCRIBE("initialize instance with value=5.5", {
		BEFORE_EACH({
			node = new nerone::NerNode(5.5);
		});
		AFTER_EACH({
			delete node;
		});
		
		IT("should return 5 when `get_value` called", {
			EXPECT(node->get_value()).toBe(5.5);
		});
	});
	
	DESCRIBE("initialize instance with value=8.9 and act_fn", {
		BEFORE_EACH({
			node = new nerone::NerNode(8.9, [](nerone::value_t a){ return a*2; });
		});
		AFTER_EACH({
			delete node;
		});
		
		IT("should return 8.9 when `get_value` is called", {
			EXPECT(node->get_value()).toBe(8.9);
		});
		
		IT("should return activation function when `get_act_fn` is called", {
			EXPECT(node->get_act_fn()(1.1)).toBe(2.2);
		});
	});
	
});

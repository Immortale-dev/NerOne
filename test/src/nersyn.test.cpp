SCENARIO_START

DESCRIBE("NerSyn", {
	using namespace nerone;
	
	NerSyn* syn;
	
	DESCRIBE("initialize default constructor instance", {
		BEFORE_EACH({
			syn = new NerSyn();
		});
		AFTER_EACH({
			delete syn;
		});
		
		IT("`get_node` should return `nullptr`", {
			EXPECT(syn->get_node()).toBeNullPtr();
		});
		
		IT("setting weight should return this weight with `get_weight`", {
			syn->set_weight(12.45);
			
			EXPECT(syn->get_weight()).toBe(12.45);
		});
		
		IT("setting the note, should return this node with `get_node`", {
			auto node = std::make_shared<NerNode>();
			syn->set_node(node);
			
			EXPECT(syn->get_node()).toBe(node);
		});
	});
	
	DESCRIBE("initialize constructor with weight and node", {
		BEFORE_EACH({
			syn = new NerSyn(std::make_shared<NerNode>(), 43.21);
		});
		AFTER_EACH({
			delete syn;
		});
		
		IT("should return 43.21 when `get_weight` is called", {
			EXPECT(syn->get_weight()).toBe(43.21);
		});
		
		IT("should not return nullptr when get_node is called", {
			EXPECT(syn->get_node()).NOT().toBeNullPtr();
		});
	});
});

SCENARIO_END

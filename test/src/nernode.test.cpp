DESCRIBE("NerNode", {
	nerone::NerNode* node;
	
	DESCRIBE("initialize default constructor instance", {
		
		BEFORE_EACH({
			node = new nerone::NerNode();
		});
		
		AFTER_EACH({
			delete node;
		});
		
		IT("Should succeed", {
			EXPECT(node->get_syns()).toBe({});
		});
		
	});
	
});

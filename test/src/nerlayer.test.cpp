DESCRIBE("NerLayer", {
	using namespace nerone;
	
	NerLayer* layer;
	
	DESCRIBE("initialize layer with default constructor", {
		BEFORE_EACH({
			layer = new NerLayer();
		});
		AFTER_EACH({
			delete layer;
		});
		
		IT("should retunr 0 when `size` is called", {
			EXPECT(layer->size()).toBe(0);
		});
		
		IT("should return 1 for the `size` when the list of nodes is set by calling `set_nodes`", {
			layer->set_nodes({std::make_shared<NerNode>()});
			
			EXPECT(layer->size()).toBe(1);
		});
		
		IT("should return 1 for the `size` when the list of nodes is set by equasion operator", {
			layer->get_nodes() = {std::make_shared<NerNode>()};
			
			EXPECT(layer->size()).toBe(1);
		});
	});
	
	DESCRIBE("initialize layer with the list of nodes", {
		shared_node_t node;
		BEFORE_EACH({
			node = std::make_shared<NerNode>();
			layer = new NerLayer({node});
		});
		AFTER_EACH({
			delete layer;
		});
		
		IT("should return 1 when the `size` is called", {
			EXPECT(layer->size()).toBe(1);
		});
		
		IT("should return the node when [0] operator is called", {
			EXPECT((*layer)[0]).toBe(node);
		});
		
		IT("should set new node when equasion operator is used with [] operator", {
			(*layer)[0] = std::make_shared<NerNode>();
			
			EXPECT((*layer)[0]).NOT().toBe(node);
		});
	});
});

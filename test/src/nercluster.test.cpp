DESCRIBE("NerCluster", {
	using namespace nerone;
	
	NerCluster* cluster;
	
	DESCRIBE("initialize with default constructor", {
		BEFORE_EACH({
			cluster = new NerCluster();
		});
		AFTER_EACH({
			delete cluster;
		});
		
		IT("should return empty list when `get_layers` is called", {
			EXPECT(cluster->get_layers().size()).toBe(0);
		});
		
		IT("should return not empty list when the list is set", {
			cluster->set_layers({std::make_shared<NerLayer>()});
			
			EXPECT(cluster->get_layers().size()).toBe(1);
		});
		
		IT("should return not empty list when the list is set by equation operator", {
			cluster->get_layers() = {std::make_shared<NerLayer>()};
			
			EXPECT(cluster->get_layers().size()).toBe(1);
		});
	});
	
	DESCRIBE("initialize with list of layers", {
		BEFORE_EACH({
			cluster = new NerCluster({std::make_shared<NerLayer>()});
		});
		AFTER_EACH({
			delete cluster;
		});
		
		IT("should return 1 when `get_layers` is called", {
			EXPECT(cluster->get_layers().size()).toBe(1);
		});
	});
});

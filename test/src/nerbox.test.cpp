class TMul {
	public:
		void operator()(nerone::shared_cluster_t cluster, nerone::value_list_t&& values) {
			test_val = cluster->get_layers().size() * 1000 + 1;
		}
		static void clear_test() {
			test_val = 0;
		}
		static int test_val;
};
int TMul::test_val = 0;

class TTec {
	public:
		void operator()(nerone::shared_cluster_t cluster, nerone::value_list_t&& values) {
			test_val = cluster->get_layers().size() * 1000 + 2;
		}
		static void clear_test() {
			test_val = 0;
		}
		static int test_val;
};
int TTec::test_val = 0;

SCENARIO_START

DESCRIBE("NerBox", {
	using namespace nerone;
	
	NerBox<TMul, TTec>* nb;
	
	DESCRIBE("initialize with default constructor", {
		BEFORE_EACH({
			nb = new NerBox<TMul, TTec>();
		});
		AFTER_EACH({
			delete nb;
		});
		
		IT("should return nullptr when `get_cluster` is called", {
			EXPECT(nb->get_cluster()).toBeNullPtr();
		});
		
		IT("should return cluster when it is set by `set_cluster` method", {
			nb->set_cluster(std::make_shared<NerCluster>());
			
			EXPECT(nb->get_cluster()).NOT().toBeNullPtr();
		});
		
		IT("calling `question` should throw", {
			EXPECT([nb](){ nb->question({1.1,2.2}); }).toThrowError();
		});
		
		IT("calling `correct` should throw", {
			EXPECT([nb](){ nb->correct({1.1,2.2}); }).toThrowError();
		});
		
		IT("calling `teach` should throw", {
			EXPECT([nb](){ nb->teach({1.1,2.2}, {3.3,4.4}); }).toThrowError();
		});
	});
	
	DESCRIBE("initialize with cluster set containing of one layer with 2 nodes", {
		BEFORE_EACH({
			nb = new NerBox<TMul, TTec>(
				std::make_shared<NerCluster>(
					layer_list_t{
						std::make_shared<NerLayer>(
							node_list_t{
								std::make_shared<NerNode>(1.1),
								std::make_shared<NerNode>(2.2)
							}
						)
					}
				)
			);
		});
		AFTER_EACH({
			delete nb;
			TMul::clear_test();
			TTec::clear_test();
		});
		
		IT("should return cluster when `get_cluster` called", {
			EXPECT(nb->get_cluster()).NOT().toBeNullPtr();
		});
		
		IT("should throw when `question` is called with wrong amount of parameters", {
			EXPECT([nb](){ nb->question({1.1}); }).toThrowError();
			EXPECT(TMul::test_val).toBe(0);
		});
		
		IT("should throw when `correct` is called with wrong amount of parameters", {
			EXPECT([nb](){ nb->correct({1.1}); }).toThrowError();
			EXPECT(TTec::test_val).toBe(0);
		});
		
		IT("should call TMul () operator when `question` is called", {
			nb->question({1.1, 2.2});
			
			EXPECT(TMul::test_val).toBe(1001);
		});
		
		IT("should call TTec () operator when `correct` is called", {
			nb->correct({1.1, 2.2});
			
			EXPECT(TTec::test_val).toBe(1002);
		});
		
		IT("should call TMul and TTec () operators when `teach` is called", {
			nb->teach({1.1, 2.2}, {3.3, 4.4});
			
			EXPECT(TMul::test_val).toBe(1001);
			EXPECT(TTec::test_val).toBe(1002);
		});
	});
});

SCENARIO_END

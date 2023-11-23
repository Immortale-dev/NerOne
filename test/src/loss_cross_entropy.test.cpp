#include "ner_loss_cross_entropy.h"

SCENARIO_START

DESCRIBE("CrossEntropy", {
	using namespace nerone;
	
	loss::CrossEntropy loss_fn;
	
	IT("should return `1.20397` when `fun` is called with `0.9` and `0.5` parameters", {
		EXPECT(loss_fn.fun(0.9,0.5)).toBeCloseTo(1.20397, 0.00001);
	});
	
	IT("should return `4.44444` when `grad` is called with `0.9` and `0.5` parameters", {
		EXPECT(loss_fn.grad(0.9,0.5)).toBeCloseTo(4.44444, 0.00001);
	});
});

SCENARIO_END

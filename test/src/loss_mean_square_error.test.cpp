#include "ner_loss_mean_square_error.h"

SCENARIO_START

DESCRIBE("loss::MeanSquareError", {
	using namespace nerone;
	
	loss::MeanSquareError loss_fn;
	
	IT("should return `8` when `fun` is called with `5` and `1` parameters", {
		EXPECT(loss_fn.fun(5.0,1.0)).toBe(8);
	});
	
	IT("should return `4` when `grad` is called with `5` and `1` parameters", {
		EXPECT(loss_fn.grad(5.0,1.0)).toBe(4);
	});
});

SCENARIO_END

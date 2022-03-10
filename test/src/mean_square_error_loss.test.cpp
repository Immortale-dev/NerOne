#include "mean_square_error_loss.hpp"

SCENARIO_START

DESCRIBE("MeanSquareError", {
	using namespace nerone;
	
	loss::MeanSquareError loss_fn;
	
	IT("should return `8` when `fun` is called with `5` and `1` parameters", {
		EXPECT(loss_fn.fun(5,1)).toBe(8);
	});
	
	IT("should return `4` when `grad` is called with `5` and `1` parameters", {
		EXPECT(loss_fn.grad(5,1)).toBe(4);
	});
});

SCENARIO_END

#include "activations_sigmoid.hpp"
#include "activations_tanh.hpp"

SCENARIO_START

DESCRIBE("Activation Functions", {
	using namespace nerone::activations;
	
	DESCRIBE("Sigmoid", {
		IT("should return `0.99593` when `fun(5.5)` is called", {
			EXPECT(Sigmoid::fun(5.5)).toBeCloseTo(0.99593, 0.00001);
		});
		IT("should return `0.00405344` when `grad(0.99593)` is called", {
			EXPECT(Sigmoid::grad(0.99593)).toBeCloseTo(0.00405344, 0.00001);
		});
	});
	
	DESCRIBE("TanH", {
		IT("should return `0.997283` when `fun(3.3) is called`", {
			EXPECT(TanH::fun(3.3)).toBeCloseTo(0.997283,0.00001);
		});
		IT("should return `0.00542662` when `grad(0.997283)` is called", {
			EXPECT(TanH::grad(0.997283)).toBeCloseTo(0.00542662,0.00001);
		});
	});
});

SCENARIO_END

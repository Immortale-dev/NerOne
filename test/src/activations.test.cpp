#include "activations_sigmoid.hpp"
#include "activations_tanh.hpp"
#include "activations_relu.hpp"

SCENARIO_START

DESCRIBE("Activation Functions", {
	using namespace nerone::activations;
	
	DESCRIBE("Sigmoid", {
		IT("should return `0.99593` when `fun(5.5)` is called", {
			EXPECT(Sigmoid::fun(5.5)).toBeCloseTo(0.99593, 0.00001);
		});
		IT("should return `0.00405344` when `grad(5.5)` is called", {
			EXPECT(Sigmoid::grad(5.5)).toBeCloseTo(0.00405344, 0.00001);
		});
	});
	
	DESCRIBE("TanH", {
		IT("should return `0.997283` when `fun(3.3) is called`", {
			EXPECT(TanH::fun(3.3)).toBeCloseTo(0.997283,0.00001);
		});
		IT("should return `0.00542662` when `grad(3.3)` is called", {
			EXPECT(TanH::grad(3.3)).toBeCloseTo(0.00542662,0.00001);
		});
	});
	
	DESCRIBE("ReLU", {
		IT("should return `15` when `fun(15)` is called", {
			EXPECT(ReLU::fun(15)).toBe(15);
		});
		IT("should return `0.5` when `fun(0.5)` is called", {
			EXPECT(ReLU::fun(0.5)).toBe(0.5);
		});
		IT("should return `0` when `fun(-2)` is called", {
			EXPECT(ReLU::fun(-2)).toBe(0);
		});
		IT("should return `0` when `fun(0)` is called", {
			EXPECT(ReLU::fun(0)).toBe(0);
		});
		
		IT("should return `1` when `grad(15)` is called", {
			EXPECT(ReLU::grad(15)).toBe(1);
		});
		IT("should return `1` when `grad(0.5)` is called", {
			EXPECT(ReLU::grad(0.5)).toBe(1);
		});
		IT("should return `0` when `grad(-2)` is called", {
			EXPECT(ReLU::grad(-2)).toBe(0);
		});
		IT("should return `1` when `grad(0)` is called", {
			EXPECT(ReLU::grad(0)).toBe(1);
		});
	});
});

SCENARIO_END

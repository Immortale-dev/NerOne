#include "ner_activation_sigmoid.h"
#include "ner_activation_tanh.h"
#include "ner_activation_relu.h"
#include "ner_activation_elu.h"
#include "ner_activation_swish.h"
#include "ner_activation_gelu.h"
#include "ner_activation_selu.h"

SCENARIO_START

DESCRIBE("Activation Functions", {
	using namespace nerone::activation;
	
	using ReLUZ = ReLU<>;
	
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
			EXPECT(ReLUZ::fun(15.0)).toBe(15.0);
		});
		IT("should return `0.5` when `fun(0.5)` is called", {
			EXPECT(ReLUZ::fun(0.5)).toBe(0.5);
		});
		IT("should return `0` when `fun(-2)` is called", {
			EXPECT(ReLUZ::fun(-2.0)).toBe(0);
		});
		IT("should return `0` when `fun(0)` is called", {
			EXPECT(ReLUZ::fun(0.0)).toBe(0);
		});
		
		IT("should return `1` when `grad(15)` is called", {
			EXPECT(ReLUZ::grad(15.0)).toBe(1);
		});
		IT("should return `1` when `grad(0.5)` is called", {
			EXPECT(ReLUZ::grad(0.5)).toBe(1);
		});
		IT("should return `0` when `grad(-2)` is called", {
			EXPECT(ReLUZ::grad(-2.0)).toBe(0);
		});
		IT("should return `1` when `grad(0)` is called", {
			EXPECT(ReLUZ::grad(0.0)).toBe(1);
		});
		
		IT("should return `10` when `ReLU<ratio<1,10>>::fun(10)` is called", {
			EXPECT((ReLU<std::ratio<1,10>>::fun(10.0))).toBe(10);
		});
		IT("should return `-1` when `ReLU<ratio<1,10>>::fun(-10)` is called", {
			EXPECT((ReLU<std::ratio<1,10>>::fun(-10.0))).toBe(-1);
		});
		
		IT("should return `1` when `ReLU<ratio<1,10>>::grad(10)` is called", {
			EXPECT((ReLU<std::ratio<1,10>>::grad(10.0))).toBe(1);
		});
		IT("should return `0.1` when `ReLU<ratio<1,10>>::grad(-10)` is called", {
			EXPECT((ReLU<std::ratio<1,10>>::grad(-10.0))).toBeCloseTo(0.1, 0.000001);
		});
	});
	
	DESCRIBE("ELU", {
		IT("should return `0.5` when `ELU<ratio<1,10>>::fun(0.5)` is called", {
			EXPECT((ELU<std::ratio<1,10>>::fun(0.5))).toBeCloseTo(0.5,0.00001);
		});
		IT("should return `-0.0393469` when `ELU<ratio<1,10>>::fun(-0.5)` is called", {
			EXPECT((ELU<std::ratio<1,10>>::fun(-0.5))).toBeCloseTo(-0.0393469,0.00001);
		});
		
		IT("should return `1` when `ELU<ratio<1,10>>::grad(0.5)` is called", {
			EXPECT((ELU<std::ratio<1,10>>::grad(0.5))).toBe(1);
		});
		IT("should return `1` when `ELU<ratio<1,10>>::grad(0)` is called", {
			EXPECT((ELU<std::ratio<1,10>>::grad(0.0))).toBe(1);
		});
		IT("should return `` when `ELU<ratio<1,10>>::grad(-0.5)` is called", {
			EXPECT((ELU<std::ratio<1,10>>::grad(-0.5))).toBeCloseTo(0.0606531, 0.00001);
		});
	});
	
	DESCRIBE("Swish", {
		IT("should return `0.731059` when `Swish::fun(1)` is called", {
			EXPECT(Swish::fun(1.0)).toBeCloseTo(0.731059,0.00001);
		});
		IT("should return `15` when `Swish::fun(15)` is called", {
			EXPECT(Swish::fun(15.0)).toBeCloseTo(15, 0.00001);
		});
		IT("should return `0` when `Swish::fun(0)` is called", {
			EXPECT(Swish::fun(0.0)).toBe(0);
		});
		IT("should return `-0.268941` when `Swish::fun(-1)` is called", {
			EXPECT(Swish::fun(-1.0)).toBeCloseTo(-0.268941, 0.00001);
		});
		IT("should return `0` when `Swish::fun(-15)` is called", {
			EXPECT(Swish::fun(-15.0)).toBeCloseTo(0, 0.00001);
		});
		
		IT("should return `0.927671` when `Swish::grad(1)` is called", {
			EXPECT(Swish::grad(1.0)).toBeCloseTo(0.927671,0.00001);
		});
		IT("should return `1` when `Swish::grad(15)` is called", {
			EXPECT(Swish::grad(15.0)).toBeCloseTo(1,0.00001);
		});
		IT("should return `0.5` when `Swish::grad(0)` is called", {
			EXPECT(Swish::grad(0.0)).toBeCloseTo(0.5,0.00001);
		});
		IT("should return `0.0723295` when `Swish::grad(-1)` is called", {
			EXPECT(Swish::grad(-1.0)).toBeCloseTo(0.0723295,0.00001);
		});
		IT("should return `0` when `Swish::grad(-15)` is called", {
			EXPECT(Swish::grad(-15.0)).toBeCloseTo(0,0.00001);
		});
	});
	
	DESCRIBE("GELU", {
		IT("should return `0.841192` when `GELU::fun(1)` is called", {
			EXPECT(GELU::fun(1.0)).toBeCloseTo(0.841192, 0.00001);
		});
		IT("should return `5` when `GELU::fun(5)` is called", {
			EXPECT(GELU::fun(5.0)).toBeCloseTo(5, 0.0001);
		});
		IT("should return `0` when `GELU::fun(0)` is called", {
			EXPECT(GELU::fun(0.0)).toBeCloseTo(0, 0.00001);
		});
		IT("should return `-0.158808` when `GELU::fun(-1)` is called", {
			EXPECT(GELU::fun(-1.0)).toBeCloseTo(-0.158808, 0.00001);
		});
		IT("should return `0` when `GELU::fun(-5)` is called", {
			EXPECT(GELU::fun(-5.0)).toBeCloseTo(0, 0.00001);
		});
		
		IT("should return `1.08296` when `GELU::grad(1)` is called", {
			EXPECT(GELU::grad(1.0)).toBeCloseTo(1.08296, 0.00001);
		});
		IT("should return `1` when `GELU::grad(5)` is called", {
			EXPECT(GELU::grad(5.0)).toBeCloseTo(1, 0.00001);
		});
		IT("should return `0.5` when `GELU::grad(0)` is called", {
			EXPECT(GELU::grad(0.0)).toBeCloseTo(0.5, 0.00001);
		});
		IT("should return `-0.0829639` when `GELU::grad(-1)` is called", {
			EXPECT(GELU::grad(-1.0)).toBeCloseTo(-0.0829639, 0.00001);
		});
		IT("should return `0` when `GELU::grad(-5)` is called", {
			EXPECT(GELU::grad(-5.0)).toBeCloseTo(0, 0.00001);
		});
	});
	
	DESCRIBE("SELU", {
		IT("should return `1.0507` when `GELU::fun(1)` is called", {
			EXPECT(SELU::fun(1.0)).toBeCloseTo(1.0507, 0.00001);
		});
		IT("should return `15.7605` when `GELU::fun(15)` is called", {
			EXPECT(SELU::fun(15.0)).toBeCloseTo(15.760515, 0.00001);
		});
		IT("should return `0` when `GELU::fun(0)` is called", {
			EXPECT(SELU::fun(0.0)).toBeCloseTo(0, 0.00001);
		});
		IT("should return `-1.11133` when `GELU::fun(-1)` is called", {
			EXPECT(SELU::fun(-1.0)).toBeCloseTo(-1.11133, 0.00001);
		});
		IT("should return `-1.7581` when `GELU::fun(-15)` is called", {
			EXPECT(SELU::fun(-15.0)).toBeCloseTo(-1.7581, 0.00001);
		});
		
		IT("should return `1.0507` when `GELU::grad(1)` is called", {
			EXPECT(SELU::grad(1.0)).toBeCloseTo(1.0507, 0.00001);
		});
		IT("should return `1.0507` when `GELU::fun(15)` is called", {
			EXPECT(SELU::grad(15.0)).toBeCloseTo(1.0507, 0.00001);
		});
		IT("should return `1.7581` when `GELU::fun(0)` is called", {
			EXPECT(SELU::grad(0.0)).toBeCloseTo(1.7581, 0.00001);
		});
		IT("should return `0.646769` when `GELU::fun(-1)` is called", {
			EXPECT(SELU::grad(-1.0)).toBeCloseTo(0.646769, 0.00001);
		});
		IT("should return `0` when `GELU::fun(-15)` is called", {
			EXPECT(SELU::grad(-15.0)).toBeCloseTo(0, 0.00001);
		});
	});
});

SCENARIO_END

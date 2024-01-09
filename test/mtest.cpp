#include <iostream>
#include <memory>
#include <cstdlib>

#include "ner_one.h"
#include "src/build_helpers.cpp"

using ExecutionCase = nerone::GDProducer<nerone::value::Cumulative<float>>::ExecutionCase;
using ExecutionResult = nerone::GDProducer<nerone::value::Cumulative<float>>::ExecutionResult;

const double PI = 3.1415;

float rand_double() {
	return (rand()%10000)/(float)10000;
}

// Structure defining point on a plane, and bool parameter defining
// if the point belongs to red team or to blue team (true and false)
struct Point {
	double x;
	double y;
	bool red;
};

// Creates set of points devided for 2 sections, and puts red points
// to the top-right area of the plane, and blue points to the
// bottom-right are of the plane.
std::vector<Point> create_labeled_inputs_zones_2() {
	std::vector<Point> res;
	
	// top-right zone
	for(int i=0;i<100;i++){
		double len = rand_double() * 15;
		double a = rand_double() * PI * 2;
		res.push_back({len * std::sin(a) + 65, len * std::cos(a) + 35, true});
	}
	
	// bottom-left zone
	for(int i=0;i<100;i++){
		double len = rand_double() * 15;
		double a = rand_double() * PI * 2;
		res.push_back({len * std::sin(a) + 35, len * std::cos(a) + 65, false});
	}
	
	return res;
}

float norm(float a) {
	return a / 100 * 2 - 1;
}

void print_tests_result(std::vector<ExecutionCase> tests, std::vector<ExecutionResult> res) {
	for(int i=0;i<(int)tests.size();i++) {
		std::cout << tests[i].values[0] << " " << tests[i].values[1] << " " << res[i].values[0] << " " << res[i].values[1] << std::endl;
	}
}

int main() {
	srand(12345);
	auto *gd = new nerone::GDProducer<nerone::value::Cumulative<float>>();
	
	std::vector<int> layers{2, 6, 6, 2};
	std::vector<std::vector<float>> weights;
	for(int i=1;i<(int)layers.size();i++) {
		int cnt = (layers[i-1]+1) * layers[i];
		std::vector<float> layer;
		for(int j=0;j<cnt;j++) {
			layer.push_back(rand_double());
		}
		weights.push_back(layer);
	}
	
	ConnectedLayerBuilder b(true);
	b.add(layers[0], nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>);
	for(int i=1;i<(int)layers.size();i++) {
		b.add(layers[i], nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>);
	}
	b.withLoss(nerone::loss::CrossEntropy::fun<float>, nerone::loss::CrossEntropy::grad<float>);
	b.withWeights(weights);
	
	auto [body, loss] = b.build();
	gd->set_body_cell(body);
	gd->set_loss_cell(loss);
	
	gd->set_learning_rate(0.01);
	gd->set_batch_size(1);
	gd->set_randomized(true);
	
	auto points = create_labeled_inputs_zones_2();
	std::vector<ExecutionCase> cases;
	for(auto &p : points) {
		cases.push_back({{norm(p.x), norm(p.y)}, {p.red ? 1.0f : 0.0f, p.red ? 0.0f : 1.0f}});
	}

	for(int i=0;i<100;i++) {
		gd->train(cases);
	}
	
	std::vector<ExecutionCase> tests;
	for(int i=0;i<100;i++) {
		for(int j=0;j<100;j++) {
			tests.push_back({
				{norm(j), norm(i)},
				{}
			});
		}
	}
	
	auto res = gd->execute(tests);
	
	// print_tests_result(tests, res);
	
	return 0;
}

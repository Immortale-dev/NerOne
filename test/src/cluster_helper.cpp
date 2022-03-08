#include <vector>
#include <utility>

#include "nercluster.hpp"
#include "nerlayer.hpp"
#include "nerhelp.hpp"
#include "nernode.hpp"
#include "nersyn.hpp"


//using namespace nerone;
//using namespace std;

using std::vector;
using std::make_shared;

nerone::shared_cluster_t generate_cluster(vector<vector<vector<nerone::value_t>>> vec, bool has_biases=false) {
	vector<nerone::shared_layer_t> layers;
	
	bool first_layer = true;
	
	for(auto& l : vec) {
		
		vector<nerone::shared_node_t> nodes;
		
		nerone::shared_node_t bias = nullptr;
		if(has_biases) {
			bias = make_shared<nerone::NerNode>(1);
		}
		
		for(auto& n : l) {
			vector<nerone::shared_syn_t> syns;
			
			int sind=0;
			for(auto s : n){
				nerone::shared_node_t prev = nullptr;
				if(!first_layer) {
					if(!has_biases || sind < (int)n.size()-1) {
						prev = (*layers[layers.size()-1])[sind++];
					} else {
						prev = layers[layers.size()-1]->get_bias();
					}
				}
				syns.push_back(make_shared<nerone::NerSyn>(prev, s));
			}
			
			nerone::act_fn_t fn = nullptr;
			if(!first_layer){
				fn = [](nerone::value_t val){return val*2;};
			}
			
			auto node = make_shared<nerone::NerNode>(0, fn);
			node->set_syns(syns);
			
			nodes.push_back(node);
		}
		
		layers.push_back(make_shared<nerone::NerLayer>(nodes));
		if(has_biases) {
			layers[layers.size()-1]->set_bias(bias);
		}
		first_layer = false;
	}
	
	return make_shared<nerone::NerCluster>(layers);
}

nerone::shared_cluster_t generate_cluster_342() {
	return generate_cluster({
		{
			{},
			{},
			{}
		},
		{
			{1.1, 1.2, -1.3},
			{1.5, -1.6, 1.7},
			{1.8, 1.9, 2.0},
			{2.1, 2.2, -2.3}
		},
		{
			{0.55, 0.65, -0.75, 0.85},
			{-0.5, 0.1, 0.2, 0.3}
		}
	});
}

nerone::shared_cluster_t generate_cluster_342B() {
	return generate_cluster({
		{
			{},
			{},
			{}
		},
		{
			{1.1, 1.2, -1.3, 0.15},
			{1.5, -1.6, 1.7, 0.25},
			{1.8, 1.9, 2.0, 0.35},
			{2.1, 2.2, -2.3, 0.45}
		},
		{
			{0.55, 0.65, -0.75, 0.85, 0.5},
			{-0.5, 0.1, 0.2, 0.3, 0.5}
		}
	}, true);
}

nerone::value_list_t get_last_layer_values(nerone::shared_cluster_t cluster) {
	auto& layers = cluster->get_layers();
	auto& last_layer = layers[layers.size()-1];
	nerone::value_list_t res(last_layer->size());
	for(size_t i=0;i<last_layer->size();i++){
		res[i] = (*last_layer)[i]->get_output();
	}
	return res;
}



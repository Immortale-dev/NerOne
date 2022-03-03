#include <vector>
#include <utility>

#include "nercluster.hpp"
#include "nerlayer.hpp"
#include "nernode.hpp"
#include "nersyn.hpp"


//using namespace nerone;
//using namespace std;

using std::vector;
using std::make_shared;

nerone::shared_cluster_t generate_cluster(vector<vector<vector<nerone::value_t>>> vec) {
	vector<nerone::shared_layer_t> layers;
	
	bool first_layer = true;
	
	for(auto& l : vec) {
		
		vector<nerone::shared_node_t> nodes;
		
		for(auto& n : l) {
			vector<nerone::shared_syn_t> syns;
			
			int sind=0;
			for(auto s : n){
				nerone::shared_node_t prev = nullptr;
				if(!first_layer) {
					prev = (*layers[layers.size()-1])[sind++];
				}
				syns.push_back(make_shared<nerone::NerSyn>(prev, s));
			}
			
			auto node = make_shared<nerone::NerNode>(0, [](nerone::value_t val){return val*2;});
			node->set_syns(syns);
			
			nodes.push_back(node);
		}
		
		layers.push_back(make_shared<nerone::NerLayer>(nodes));
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

nerone::value_list_t get_last_layer_values(nerone::shared_cluster_t cluster) {
	auto& layers = cluster->get_layers();
	auto& last_layer = layers[layers.size()-1];
	nerone::value_list_t res(last_layer->size());
	for(size_t i=0;i<last_layer->size();i++){
		res[i] = (*last_layer)[i]->get_value();
	}
	return res;
}



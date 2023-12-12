#include "ner_help.h"
#include "ner_cell_o.h"
#include "ner_cell_t.h"

template<typename VT, int I, int O>
class TestOCell : public nerone::cell::OCell<VT> {
	public:
		TestOCell() {
			for(int i=0;i<I;i++) {
				inputs.push_back(std::make_shared<VT>());
			}
			for(int i=0;i<O;i++) {
				outputs.push_back(std::make_shared<VT>());
			}
		}
		void calc_value() {
			float res = 0;
			for(auto it : inputs) {
				res += this->cast_value(it)->get();
			}
			
			int i=0;
			for(auto it : outputs) {
				i++;
				this->cast_value(it)->set(res * (float)i);
			}
		}
		void calc_grad() {
			float res = 0;
			for(auto it : outputs) {
				res += this->cast_value(it)->get_grad();
			}
			
			int i=1;
			for(auto it : inputs) {
				i++;
				this->cast_value(it)->set_grad(res * (float)i);
			}
		}
		void clean() {
			for(auto it : inputs) {
				this->cast_value(it)->clean();
			}
			for(auto it : outputs) {
				this->cast_value(it)->clean();
			}
		}
		void start() {}
		void finish() {}
		
		const nerone::value_list_t& get_inputs() {
			return inputs;
		}
		const nerone::value_list_t& get_outputs() {
			return outputs;
		}
		void set_inputs(nerone::value_list_t vals) {
			for(size_t i=0;i<inputs.size();i++) {
				inputs[i] = vals[i];
			}
		}
		void set_outputs(nerone::value_list_t vals) {
			for(size_t i=0;i<outputs.size();i++) {
				outputs[i] = vals[i];
			}
		}
		
	private:
		nerone::value_list_t inputs;
		nerone::value_list_t outputs;
};

template<typename VT, int I, int O>
class TestTCell : public nerone::cell::TCell<VT> {
	using weight_list_t = typename nerone::cell::TCell<VT>::weight_list_t;
	public:
		TestTCell() {
			for(int i=0;i<I;i++) {
				inputs.push_back(std::make_shared<VT>());
			}
			for(int i=0;i<O;i++) {
				outputs.push_back(std::make_shared<VT>());
			}
		}
		void calc_value() {
			float res = 0;
			for(auto it : inputs) {
				res += this->cast_value(it)->get();
			}
			
			int i=0;
			for(auto it : outputs) {
				i++;
				this->cast_value(it)->set(res * (float)i);
			}
		}
		void calc_grad() {
			float res = 0;
			for(auto it : outputs) {
				res += this->cast_value(it)->get_grad();
			}
			
			int i=1;
			for(auto it : inputs) {
				i++;
				this->cast_value(it)->set_grad(res * (float)i);
			}
		}
		void clean() {
			for(auto it : inputs) {
				this->cast_value(it)->clean();
			}
			for(auto it : outputs) {
				this->cast_value(it)->clean();
			}
		}
		void start() {}
		void finish() {}
		
		const nerone::value_list_t& get_inputs() {
			return inputs;
		}
		const nerone::value_list_t& get_outputs() {
			return outputs;
		}
		void set_inputs(nerone::value_list_t vals) {
			for(size_t i=0;i<inputs.size();i++) {
				inputs[i] = vals[i];
			}
		}
		void set_outputs(nerone::value_list_t vals) {
			for(size_t i=0;i<outputs.size();i++) {
				outputs[i] = vals[i];
			}
		}
		
		const weight_list_t& get_weights() {
			return weights;
		}
		void set_weights(weight_list_t weights) {
			this->weights = weights;
		}
		void update(nerone::shared_train_data_t data) {
			updated_times++;
		}
		
		int get_updated_times() {
			return updated_times;
		}
		
	private:
		nerone::value_list_t inputs;
		nerone::value_list_t outputs;
		weight_list_t weights;
		int updated_times = 0;
};

class ConnectedLayerBuilder {
	using VT = nerone::value::Cumulative<float>;
	using BVT = nerone::value::CumulativeBias<float>;
	public:
		ConnectedLayerBuilder(bool with_biases): _with_biases(with_biases) {}
		ConnectedLayerBuilder& add(int layer_size, nerone::act_fn_t<float> act, nerone::act_fn_t<float> grad) {
			std::vector<nerone::shared_cell_t> act_cells;
			for(int i=0;i<layer_size;i++) {
				act_cells.push_back(std::make_shared<nerone::cell::Activation<VT>>(act, grad));
			}
			nerone::shared_cell_t cell = std::make_shared<nerone::cell::Layer<VT>>(act_cells);
			_layers.push_back(cell);
			if (_layers.size() > 1) {
				create_connection(_layers[_layers.size()-2], _layers[_layers.size()-1]);
			}
			return *this;
		}
		ConnectedLayerBuilder& withLoss(nerone::loss_fn_t<float> act, nerone::loss_fn_t<float> grad) {
			_fn = act;
			_grad = grad;
			return *this;
		}
		ConnectedLayerBuilder& withWeights(std::vector<std::vector<float>> weights) {
			for(size_t i=0;i<_segments.size();i++) {
				_segments[i]->set_weights(weights[i]);
			}
			return *this;
		}
		std::pair<std::shared_ptr<nerone::cell::Cluster<VT>>, std::shared_ptr<nerone::cell::LossLayer<VT>>> build() {
			std::vector<nerone::shared_cell_t> list, loss_list;
			for(size_t i=0;i<_layers.size();i++) {
				list.push_back(_layers[i]);
				if (i < _layers.size()-1) {
					list.push_back(_segments[i]);
				}
			}
			
			auto& last_layer = std::static_pointer_cast<nerone::cell::Layer<VT>>(_layers.back())->get_cells();
			for(size_t i=0;i<last_layer.size();i++) {
				auto lossCell = std::make_shared<nerone::cell::Loss<VT>>(_fn, _grad);
				lossCell->set_input(last_layer[i]->get_outputs().front());
				loss_list.push_back(lossCell);
			}
			
			auto body = std::make_shared<nerone::cell::Sequence<VT>>(list);
			auto loss = std::make_shared<nerone::cell::LossLayer<VT>>(loss_list);
						
			return {body, loss};
		}
		
	private:
		bool _with_biases;
		std::vector<nerone::shared_cell_t> _layers;
		std::vector<std::shared_ptr<nerone::cell::Segment<VT>>> _segments;
		std::shared_ptr<nerone::cell::Cluster<VT>> _body;
		std::shared_ptr<nerone::cell::LossLayer<VT>> _loss;
		nerone::loss_fn_t<float> _fn, _grad;
		
		void create_connection(nerone::shared_cell_t left, nerone::shared_cell_t right) {
			std::vector<nerone::shared_value_t> segInputs = left->get_outputs();
			std::vector<nerone::shared_value_t> segOutputs = right->get_inputs();
			segInputs.push_back(std::make_shared<BVT>());
			
			_segments.push_back(std::make_shared<nerone::cell::Segment<VT>>(segInputs, segOutputs));
		}
};

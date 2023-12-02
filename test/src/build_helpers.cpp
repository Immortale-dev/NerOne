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

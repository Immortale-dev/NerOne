#ifndef _NN_NER_PRODUCER_GD
#define _NN_NER_PRODUCER_GD

#include <vector>
#include <optional>
#include <stdexcept>

#include "ner_help.h"
#include "ner_producer.h"

namespace nerone {
	/**
	 * The Gradient Descent Producer drive all of the procesess related
	 * to training the neural network, and executing queries.
	 */
	template<typename VT>
	class GDProducer : public Producer<VT> {
		using f_type = typename VT::f_type;
		public:
			using Producer<VT>::Producer;
			
			struct ExecutionCase {
				using list_t = std::vector<f_type>;
				list_t values;
				list_t expected;
			};
			struct ExecutionResult {
				using list_t = std::vector<f_type>;
				list_t values;
				list_t errors;
			};
			
			struct GDSettings {
				float learning_rate;
				size_t batch_size;
				bool randomized;
			};
		
			void start_training();
			void finish_training();
			
			std::vector<ExecutionResult> train_partial(std::vector<ExecutionCase> list, GDSettings);
			std::vector<ExecutionResult> train(std::vector<ExecutionCase> list, GDSettings);
			std::vector<ExecutionResult> train_partial(std::vector<ExecutionCase> list);
			std::vector<ExecutionResult> train(std::vector<ExecutionCase> list);
			
			void start_executing();
			void finish_executing();
			
			std::vector<ExecutionResult> execute_partial(std::vector<ExecutionCase> list);
			std::vector<ExecutionResult> execute(std::vector<ExecutionCase> list);
			
			void set_learning_rate(float rate);
			void set_batch_size(size_t batch_size);
			void set_randomized(bool randomized);
			
			float get_learning_rate();
			size_t get_batch_size();
			bool get_randomized();
			
			void apply_settings(GDSettings settings);
			
		private:
			void consume();
			void clean();
			
			ExecutionResult train_partial(ExecutionCase& cs);
			ExecutionResult execute_partial(ExecutionCase& cs);
		
			bool _executing = false;
			bool _training = false;
			
			float _rate = 0.01;
			size_t _batch_size = 10;
			bool _randomized = false;
			
			size_t _step = 0;
	};
}

#include "ner_producer_gd.hpp"

#endif // _NN_NER_PRODUCER_GD

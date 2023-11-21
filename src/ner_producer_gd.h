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
	class GDProducer : public Producer {
		public:
			template<typename FT>
			struct ExecutionCase {
				using list_t = std::vector<FT>;
				list_t values;
				list_t expected;
			};
			template<typename FT>
			struct ExecutionResult {
				using list_t = std::vector<FT>;
				list_t values;
				list_t errors;
			}
			
			struct GDSettings {
				float learning_rate;
				size_t batch_size;
				bool randomized;
			};
		
			void start_training();
			void finish_training();
			
			template<typename FT>
			std::vector<ExecutionResult<FT>> train_partial(std::vector<ExecutionCase<FT>> list, GDSettings);
			template<typename FT>
			std::vector<ExecutionResult<FT>> train(std::vector<ExecutionCase<FT>> list, GDSettings);
			template<typename FT>
			std::vector<ExecutionResult<FT>> train_partial(std::vector<ExecutionCase<FT>> list);
			template<typename FT>
			std::vector<ExecutionResult<FT>> train(std::vector<ExecutionCase<FT>> list);
			
			void start_executing();
			void finish_executing();
			
			template<typename FT>
			std::vector<ExecutionResult<FT>> execute_partial(std::vector<ExecutionCase<FT>> list);
			template<typename FT>
			std::vector<ExecutionResult<FT>> execute(std::vector<ExecutionCase<FT>> list);
			
			void set_learning_rate(float rate);
			void set_batch_size(size_t batch_size);
			void set_randomized(bool randomized);
			
			void apply_settings(GDSettings settings);
			
		private:
			void consume();
			void clean();
			
			template<typename FT>
			ExecutionResult<FT> train_partial(ExecutionCase<FT>& cs);
			template<typename FT>
			ExecutionResult<FT> execute_partial(ExecutionCase<FT>& cs);
		
			bool _execiting = false;
			bool _training = false;
			
			float _rate = 0.01;
			size_t _batch_size = 10;
			bool _randomized = false;
			
			size_t _step = 0;
	};
}

#include "ner_producer_gd.hpp"

#endif // _NN_NER_PRODUCER_GD

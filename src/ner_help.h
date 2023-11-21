#ifndef _NN_NER_HELP
#define _NN_NER_HELP

#include <memory>
#include <functional>
#include <vector>

namespace nerone {
	// Cell training data.
	class TrainData {
		virtual ~TrainData() {}
	};
	class GDTrainData : public TrainData {
		public:
			GDTrainData(float rate) : rate(rate) {};
			float rate;
	};
	
	// Cell command basic calss.
	class CellCommand {
		virtual ~CellCommand() {};
	};

	// Bakc decl
	namespace value {
		class Value;
	}
	namespace cell {
		class Cell;
	}

	using shared_value_t = std::shared_ptr<value::Value>;
	using shared_cell_t = std::shared_ptr<cell::Cell>;
	using shared_train_data_t = std::shared_ptr<TrainData>;
	using shared_cell_command_t = std::shared_ptr<CellCommand>;
	
	using value_list_t = std::vector<shared_value_t>;
	using cell_list_t = std::vector<shared_cell_t>;

	template<typename FT>
	using act_fn_t = std::function<FT(FT)>;
	template<typename FT>
	using loss_fn_t = std::function<FT(FT,FT)>;
}

#endif // _NN_NER_HELP

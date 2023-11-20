#ifndef NN_PRODUCER
#define NN_PRODUCER

#include <memory>

#include "nerhelp.hpp"

namespace nerone {
	class Producer {
		public:
			using body_cell_t = std::shared_ptr<ClusterCell>;
			using loss_cell_t = std::shared_ptr<LossClusterCell>;
		
			Producer() = default;
			Producer(body_cell_t body, loss_cell_t loss) : _body(body), _loss(loss) {}
			virtual ~Producer() {}
			virtual void set_body_cell(body_cell_t body) { _body = body; }
			virtual void set_loss_cell(loss_cell_t loss) { _loss = loss; }
			virtual body_cell_t get_body_cell() { return _body; }
			virtual loss_cell_t get_loss_cell() { return _loss; }
			
		protected:
			body_cell_t _body;
			loss_cell_t _loss;
	};
}

#endif NN_PRODUCER
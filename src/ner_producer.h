#ifndef _NN_NER_PRODUCER
#define _NN_NER_PRODUCER

#include <memory>

#include "ner_help.h"
#include "ner_cell_cluster.h"
#include "ner_cell_loss_layer.h"

namespace nerone {
	template<typename VT>
	class Producer {
		public:
			using body_cell_t = std::shared_ptr<cell::Cluster<VT>>;
			using loss_cell_t = std::shared_ptr<cell::LossLayer<VT>>;
		
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

#endif // _NN_NER_PRODUCER

#include "ner_producer_gd.h"

void nerone::GDProducer::start_training() {
	if (_training) {
		throw new std::logic_error("training is in progress.");
	}
	if (_executing) {
		throw new std::logic_error("execution is in progress.");
	}
	_step = 0;
	_training = true;
	_body->start();
	_loss->start();
}

void nerone::GDProducer::finish_training() {
	if (!_training) {
		throw new std::logic_error("training was not started");
	}
	if (_step > 0) {
		consume();
		clean();
	}
	_body->finish();
	_loss->finish();
	_training = false;
}

void nerone::GDProducer::start_executing() {
	if (_training) {
		throw new std::logic_error("training is in progress.");
	}
	if (_executing) {
		throw new std::logic_error("execution is in progress.");
	}
	_step = 0;
}

void nerone::GDProducer::finish_executing() {
	if (!_training) {
		throw new std::logic_error("execution was not started");
	}
	clean();
	_body->finish();
	_loss->finish();
	_executing = false;
}

void nerone::GDProducer::set_learning_rate(float rate) {
	_rate = rate;
}

void nerone::GDProducer::set_batch_size(size_t batch_size) {
	_batch_size = batch_size;
}

void nerone::GDProducer::set_randomized(bool randomized) {
	_randomized = randomized;
}

void nerone::GDProducer::consume() {
	_body->update(std::make_shared<GDTrainData>(_rate));
}
void nerone::GDProducer::clean() {
	_body->clean();
	_loss->clean();
}

void nerone::GDProducer::apply_settings(GDSettings settings) {
	_batch_size = settings.batch_size;
	_rate = settings.learning_rate;
	_randomized = settings.randomized;
}


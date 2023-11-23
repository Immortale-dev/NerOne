template<typename VT>
void nerone::GDProducer<VT>::start_training() {
	if (_training) {
		throw new std::logic_error("training is in progress.");
	}
	if (_executing) {
		throw new std::logic_error("execution is in progress.");
	}
	_step = 0;
	_training = true;
	this->_body->start();
	this->_loss->start();
}

template<typename VT>
void nerone::GDProducer<VT>::finish_training() {
	if (!_training) {
		throw new std::logic_error("training was not started");
	}
	if (_step > 0) {
		consume();
		clean();
	}
	this->_body->finish();
	this->_loss->finish();
	_training = false;
}

template<typename VT>
void nerone::GDProducer<VT>::start_executing() {
	if (_training) {
		throw new std::logic_error("training is in progress.");
	}
	if (_executing) {
		throw new std::logic_error("execution is in progress.");
	}
	_step = 0;
}

template<typename VT>
void nerone::GDProducer<VT>::finish_executing() {
	if (!_training) {
		throw new std::logic_error("execution was not started");
	}
	clean();
	this->_body->finish();
	this->_loss->finish();
	_executing = false;
}

template<typename VT>
void nerone::GDProducer<VT>::set_learning_rate(float rate) {
	_rate = rate;
}

template<typename VT>
void nerone::GDProducer<VT>::set_batch_size(size_t batch_size) {
	_batch_size = batch_size;
}

template<typename VT>
void nerone::GDProducer<VT>::set_randomized(bool randomized) {
	_randomized = randomized;
}

template<typename VT>
void nerone::GDProducer<VT>::consume() {
	this->_body->update(std::make_shared<GDTrainData>(_rate));
}

template<typename VT>
void nerone::GDProducer<VT>::clean() {
	this->_body->clean();
	this->_loss->clean();
}

template<typename VT>
void nerone::GDProducer<VT>::apply_settings(GDSettings settings) {
	_batch_size = settings.batch_size;
	_rate = settings.learning_rate;
	_randomized = settings.randomized;
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::train_partial(std::vector<ExecutionCase> list, GDSettings settings) {
	apply_settings(settings);
	return train_partial(list);
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::train(std::vector<ExecutionCase> list, GDSettings settings) {
	apply_settings(settings);
	return train(list);
}

template<typename VT>
typename nerone::GDProducer<VT>::ExecutionResult nerone::GDProducer<VT>::train_partial(ExecutionCase& cs) {
	// Set initial value.
	size_t ind = 0;
	for(auto val : this->_body->get_inputs()) {
		val->set(cs.values[ind++]);
	}
	// Calc body values.
	this->_body->calc_values();
	// Get results
	std::vector<f_type> ret;
	for(auto val : this->_body->get_outputs()) {
		ret.push_back(val->get());
	}
	// Set loss expected values.
	ind = 0;
	for(auto val : this->_loss->get_expected_values()) {
		val->set(cs.expected[ind++]);
	}
	// Calc loss values.
	this->_loss->calc_values();
	// Get error values.
	std::vector<f_type> errs;
	for(auto val : this->_loss->get_outputs()) {
		errs.push_back(val->get());
	}
	// Calculate loss gradient
	this->_loss->calc_grad();
	// Calculate body gradient
	this->_body->calc_grad();
	
	// Update biases if needed.
	if (++_step >= _batch_size) {
		consume();
		clean();
		_step = 0;
	}
	
	return {ret, errs};
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::train_partial(std::vector<ExecutionCase> list) {
	std::vector<size_t> indexes(list.size());
	for(size_t i=0;i<list.size();i++) {
		indexes[i] = i;
	}
	if (_randomized) {
		for(size_t i=0;i<list.size();i++) {
			std::swap(indexes[i], indexes[rand()%list.size()]);
		}
	}
	std::vector<ExecutionResult> rets;
	for(size_t i=0;i<list.size();i++) {
		rets.push_back(train_partial(list[indexes[i]]));
	}
	return rets;
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::train(std::vector<ExecutionCase> list) {
	start_training();
	auto rets = train_partial(list);
	finish_training();
	return rets;
}

template<typename VT>
typename nerone::GDProducer<VT>::ExecutionResult nerone::GDProducer<VT>::execute_partial(ExecutionCase& cs) {
	// Set initial value.
	size_t ind = 0;
	for(auto val : this->_body->get_inputs()) {
		val->set(cs.values[ind++]);
	}
	// Calc body values.
	this->_body->calc_values();
	// Collect values
	std::vector<f_type> ret;
	for(auto val : this->_body->get_outputs()) {
		ret.push_back(val->get());
	}
	
	std::vector<f_type> errs;
	if (cs.expected.size()) {
		// Set loss expected values.
		ind = 0;
		for(auto val : this->_loss->get_expected_values()) {
			val->set(cs.expected[ind++]);
		}
		// Calc loss values.
		this->_loss->calc_values();
		// Get error values.
		for(auto val : this->_loss->get_outputs()) {
			errs.push_back(val->get());
		}
	}
	return {ret, errs};
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::execute_partial(std::vector<ExecutionCase> list) {
	std::vector<ExecutionResult> rets;
	for(auto& cs : list) {
		rets.push_back(execute_partial(cs));
	}
	return rets;
}

template<typename VT>
std::vector<typename nerone::GDProducer<VT>::ExecutionResult> nerone::GDProducer<VT>::execute(std::vector<ExecutionCase> list) {
	start_executing();
	auto rets = execute_partial(list);
	finish_executing();
	return rets;
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::train_partial(std::vector<ExecutionCase<FT>> list, GDSettings settings) {
	apply_settings(settings);
	return train_partial(list);
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::train(std::vector<ExecutionCase<FT>> list, GDSettings settings) {
	apply_settings(settings);
	return train(list);
}

template<typename FT>
ExecutionResult<FT> nerone::GDProducer::train_partial(ExecutionCase<FT> cs) {
	// Set initial value.
	size_t ind = 0;
	for(auto val : _body->get_inputs()) {
		val->set(cs.values[ind++]);
	}
	// Calc body values.
	_body->calc_values();
	// Get results
	std::vector<FT> ret;
	for(auto val : _body->get_outputs()) {
		ret.push_back(val->get());
	}
	// Set loss expected values.
	ind = 0;
	for(auto val : _loss->get_expected_values()) {
		val->set(cs.expected[ind++]);
	}
	// Calc loss values.
	_loss->calc_values();
	// Get error values.
	std::vector<FT> errs;
	for(auto val : _loss->get_outputs()) {
		errs.push_back(val->get());
	}
	// Calculate loss gradient
	_loss->calc_grad();
	// Calculate body gradient
	_body->calc_grad();
	
	// Update biases if needed.
	if (++_step >= _batch_size) {
		consume();
		clean();
		_step = 0;
	}
	
	return {ret, errs};
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::train_partial(std::vector<ExecutionCase<FT>> list) {
	std::vector<size_t> indexes(list.size());
	for(size_t i=0;i<list.size();i++) {
		indexes[i] = i;
	}
	if (_randomized) {
		for(size_t i=0;i<list.size();i++) {
			std::swap(indexes[i], indexes[rand()%list.size()]);
		}
	}
	std::vector<ExecutionResult<FT>> rets;
	for(size_t i=0;i<list.size();i++) {
		rets.push_back(train_partial(list[indexes[i]]));
	}
	return rets;
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::train(std::vector<ExecutionCase<FT>> list) {
	start_training();
	auto rets = train_partial(list);
	finish_training();
	return rets;
}


template<typename FT>
ExecutionResult<FT> nerone::GDProducer::execute_partial(ExecutionCase<FT> cs) {
	// Set initial value.
	size_t ind = 0;
	for(auto val : _body->get_inputs()) {
		val->set(cs.values[ind++]);
	}
	// Calc body values.
	_body->calc_values();
	// Collect values
	std::vector<FT> ret;
	for(auto val : _body->get_outputs()) {
		ret.push_back(val->get());
	}
	
	std::vector<FT> errs;
	if (cs.expected.size()) {
		// Set loss expected values.
		ind = 0;
		for(auto val : _loss->get_expected_values()) {
			val->set(cs.expected[ind++]);
		}
		// Calc loss values.
		_loss->calc_values();
		// Get error values.
		for(auto val : _loss->get_outputs()) {
			errs.push_back(val->get());
		}
	}
	return {rets, errs};
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::execute_partial(std::vector<ExecutionCase<FT>> list) {
	std::vector<ExecutionResult<FT>> rets;
	for(auto& cs : list) {
		rets.push_back(execute_partial(cs));
	}
	return rets;
}

template<typename FT>
std::vector<ExecutionResult<FT>> nerone::GDProducer::execute(std::vector<ExecutionCase<FT>> list) {
	start_executing();
	auto rets = execute_partial(list);
	finish_executing();
	return rets;
}


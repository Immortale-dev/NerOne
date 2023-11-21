template<typename T>
T nerone::value::Cumulative<T>::get() {
	return _val;
}

template<typename T>
void nerone::value::Cumulative<T>::set(T val) {
	if (!_active) {
		_val = val;
		_active = true;
		return;
	}
	_stack.push(_val);
	_val = val;
}

template<typename T>
T nerone::value::Cumulative<T>::get_grad() {
	return _grad;
}

template<typename T>
void nerone::value::Cumulative<T>::set_grad(T val) {
	_grad = val;
}

template<typename T>
void nerone::value::Cumulative<T>::pop() {
	if (_stack.empty()) {
		_active = false;
		return;
	}
	_val = _stack.top();
	_stack.pop();
}

template<typename T>
void nerone::value::Cumulative<T>::clear() {
	while(!_stack.empty()) {
		_stack.pop();
	}
	_active = false;
}

template<typename T>
bool nerone::value::Cumulative<T>::empty() {
	return !_active;
}

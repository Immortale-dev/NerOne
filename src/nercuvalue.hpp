template<typename T>
T nerone::CuValue<T>::get() {
	return _val;
}

template<typename T>
void nerone::CuValue<T>::set(T val) {
	if (!_active) {
		_val = val;
		_active = true;
		return;
	}
	_stack.push(_val);
	_val = val;
}

template<typename T>
T nerone::CuValue<T>::get_grad() {
	return _grad;
}

template<typename T>
void nerone::CuValue<T>::set_grad(T val) {
	_grad = val;
}

template<typename T>
void nerone::CuValue<T>::pop() {
	if (_stack.empty()) {
		_active = false;
		return;
	}
	_val = _stack.top();
	_stack.pop();
}

template<typename T>
void nerone::CuValue<T>::clear() {
	while(!_stack.empty()) {
		_stack.pop();
	}
	_active = false;
}

template<typename T>
bool nerone::CuValue<T>::empty() {
	return !_active;
}

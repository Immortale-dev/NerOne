template<typename T>
T nerone::CuValue::get() {
	return _stack.top();
}

template<typename T>
void nerone::CuValue::set(T val) {
	_stack.push(val);
}

template<typename T>
T nerone::CuValue::get_grad() {
	return _grad;
}

template<typename T>
void nerone::CuValue::set_grad(T val) {
	_grad = val;
}

template<typename T>
void nerone::CuValue::pop() {
	_grad.pop();
}

template<typename T>
void nerone::CuValue::clear() {
	_stack = std::stack<T>();
}

template<typename T>
bool nerone::CuValue::empty() {
	return _stack.empty();
}

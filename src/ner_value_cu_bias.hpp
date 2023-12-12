template<typename T>
T nerone::value::CumulativeBias<T>::get() {
	return _val;
}

template<typename T>
void nerone::value::CumulativeBias<T>::set(T val) {
	_val = val;
}

template<typename T>
T nerone::value::CumulativeBias<T>::get_grad() {
	// No grad for bias.
	return 0;
}

template<typename T>
void nerone::value::CumulativeBias<T>::set_grad(T val) {
	// Nothing to do.
}

template<typename T>
void nerone::value::CumulativeBias<T>::pop() {
	// Nothing to do.
}

template<typename T>
void nerone::value::CumulativeBias<T>::clean() {
	// Nothing to do.
}

template<typename T>
bool nerone::value::CumulativeBias<T>::empty() {
	// Never empty.
	return false;
}

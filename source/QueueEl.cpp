#include "../header/QueueEl.h"
#include "../header/Square.h"
#include <memory>
template<typename T>
QueueEl<T>::QueueEl(const T& val, const std::shared_ptr<QueueEl>& next)
	: val(val), next(next){}
template<typename T>
QueueEl<T>::QueueEl() :
	val(T()), next(nullptr) {}
#include "../template/QueueEl.tpp"

#include "../header/QueueEl.h"
#include "../header/Rhomb.h"
template<typename T>
QueueEl<T>::QueueEl(const T& val, const std::shared_ptr<QueueEl>& next)
	: val(val), next(next){}

#include "../template/QueueEl.tpp"

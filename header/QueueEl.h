#ifndef LISTEL_H_
#define LISTEL_H_
#include <memory>
#include "../header/Square.h"
template<typename T>
class QueueEl {
public:
	QueueEl();
	QueueEl(const T& val, const std::shared_ptr<QueueEl>& next);
	T val;
	std::shared_ptr<QueueEl> next;
};
#endif // LISTEL_H_


#ifndef ITERATOR_H_
#define ITERATOR_H_
#include "../header/QueueEl.h"
#include "../header/Queue.h"
#include "../header/Rhomb.h"
#include <memory>
template<typename T>
class Queue<T>::iterator : public std::iterator<std::forward_iterator_tag, T> {
public:
	std::weak_ptr<QueueEl<T>> prev_el;
	iterator();
	iterator(std::shared_ptr<QueueEl<T>>);
	iterator& operator++();
	T& operator*();
	bool operator!=(iterator);
	bool operator==(iterator);
	bool operator==(std::nullptr_t);
};

template class Queue<Rhomb<int>>::iterator;
#endif // ITERATOR_H_


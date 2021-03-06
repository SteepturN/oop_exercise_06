#ifndef ITERATOR_H_
#define ITERATOR_H_
#include "../header/QueueEl.h"
#include "../header/Queue.h"
#include "../header/Square.h"
#include <memory>
template<typename T, typename Alloc>
class Queue<T, Alloc>::iterator{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::size_t;
	using pointer = T*;
	using reference = T&;

	std::weak_ptr<QueueEl<T>> prev_el;
	iterator();
	iterator(std::shared_ptr<QueueEl<T>>);
	iterator& operator++();
	T& operator*();
	bool operator!=(iterator);
	bool operator==(iterator);
	bool operator==(std::nullptr_t);
};

template class Queue<Square<int>, Allocator<QueueEl<Square<int> >, 10> >::iterator;
template class Queue<Square<int>>::iterator;
#include "../template/Queue.tpp"
#endif // ITERATOR_H_


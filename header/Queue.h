#ifndef STACK_H
#define STACK_H
#include <memory>
#include "../header/QueueEl.h"
#include "../header/Rhomb.h"
#include "../header/Allocator.hpp"
template <class T, class Alloc = std::allocator<QueueEl<T>>>
class Queue {
public:
	//null - > begin
	class iterator;
	using traits = std::allocator_traits<Alloc>;
	std::shared_ptr<QueueEl<T>> zero_el;
	std::shared_ptr<QueueEl<T>> end_el;
	unsigned int size;
	Alloc alloc;

	Queue();
	~Queue();
	iterator begin();
	iterator end();

	void insert(const T& t, iterator i);
	void erase(iterator p);

	T pop();
	void push(const T&);
	T top()/*const*/;

	template <typename Y>
	friend std::ostream& operator<<(std::ostream&, Queue<Y>&);
};
#endif // STACK_H

#include "../template/Queue.tpp"

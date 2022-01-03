#ifndef STACK_H
#define STACK_H
#include <memory>
#include "../header/QueueEl.h"
#include "../header/Rhomb.h"
template <typename T>
class Queue {
public:
	//null - > begin
	class iterator;
	std::shared_ptr<QueueEl<T>> zero_el;
	std::shared_ptr<QueueEl<T>> end_el;
	unsigned int size;

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

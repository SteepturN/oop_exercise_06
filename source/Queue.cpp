#include "../header/Rhomb.h"
#include "../header/Queue.h"
#include "../header/QueueEl.h"
#include "../header/iterator.h"
#include "../header/Allocator.hpp"
#include <memory>
//""
/*
‘std::shared_ptr<QueueEl<Rhomb<int> > >::reset(Rhomb<int>*&, Queue<T, Alloc>::Queue<Rhomb<int>, std::allocator<Rhomb<int> > >::<lambda(Rhomb<int>*)>&, std::allocator<Rhomb<int> >&)’
   13 |  zero_el.reset(pointer, deleter, alloc);
      |  ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~

home/steep/educat/instit/oop/LR6/source/Queue.cpp: In instantiation of ‘Queue<T, Alloc>::Queue() [with T = Rhomb<int>; Alloc = std::allocator<Rhomb<int> >]’:
/home/steep/educat/instit/oop/LR6/source/../header/../template/Queue.tpp:2:16:   required from here
/home/steep/educat/instit/oop/LR6/source/Queue.cpp:16:15: error: no matching function for call to ‘std::shared_ptr<QueueEl<Rhomb<int> > >::reset(Rhomb<int>*&, Queue<T, Alloc>::Queue<Rhomb<int>, std::allocator<Rhomb<int> > >::<lambda(QueueEl<Rhomb<int> >*)>&, std::allocator<Rhomb<int> >&)’
   16 |  zero_el.reset(pointer, deleter, alloc);
      |  ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~

*/
template <typename T, typename Alloc> Queue<T, Alloc>::Queue()
	: zero_el(), end_el(), size(0), alloc() {
	zero_el = std::allocate_shared<QueueEl<T>>(alloc);
	end_el = zero_el;
}

template <typename T, typename Alloc> Queue<T, Alloc>::~Queue() {
	end_el = nullptr;
	zero_el = nullptr;
}
template <typename T, typename Alloc> typename Queue<T, Alloc>::iterator Queue<T, Alloc>::begin() {
	return iterator(zero_el);
}
template <typename T, typename Alloc> typename Queue<T, Alloc>::iterator Queue<T, Alloc>::end() {
	return iterator(end_el);
}

template <typename T, typename Alloc> void Queue<T, Alloc>::insert(const T& t, Queue<T, Alloc>::iterator i) { //inserts before
	if(i == nullptr) throw std::invalid_argument("null iterator");
	auto cur = i.prev_el.lock();
	cur->next =
		std::allocate_shared<QueueEl<T>>(alloc, t, cur->next);
	if(cur == end_el) end_el = cur->next;
	++size;
}
template <typename T, typename Alloc> void Queue<T, Alloc>::erase(iterator i) {
	if(i == nullptr) throw std::invalid_argument("null iterator");
	auto cur = i.prev_el.lock();
	if(cur->next == end_el) end_el = cur;
	cur->next = cur->next->next;
	--size;
}
template <typename T, typename Alloc> T Queue<T, Alloc>::pop() {
	if(zero_el->next == nullptr) throw std::out_of_range("empty queue");
	T element = *(begin());
	erase(begin());
	return element;
}
template <typename T, typename Alloc> void Queue<T, Alloc>::push(const T& el) {
	insert(el, end());
}
template <typename T, typename Alloc> T Queue<T, Alloc>::top() /*const*/{
	if(zero_el->next == nullptr) throw std::out_of_range("empty queue");
	T el = *(begin());
	return el;
}
template <typename T, typename Alloc> std::ostream& operator<<(std::ostream& cout, Queue<T, Alloc>& queue) {
    for(auto i = queue.begin(); i != queue.end(); ++i) {
        cout << *i << '\n';
    }
    return cout;
}

#include "../template/Queue.tpp"

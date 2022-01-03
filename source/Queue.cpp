#include "../header/Rhomb.h"
#include "../header/Queue.h"
#include "../header/QueueEl.h"
#include "../header/iterator.h"
//""
template <typename T> Queue<T>::Queue()
	: zero_el(new QueueEl<T>(T(), nullptr)), end_el(zero_el), size(0){}

template <typename T> Queue<T>::~Queue() {
	zero_el = nullptr;
	end_el = nullptr;
}
template <typename T> typename Queue<T>::iterator Queue<T>::begin() {
	return iterator(zero_el);
}
template <typename T> typename Queue<T>::iterator Queue<T>::end() {
	return iterator(end_el);
}

template <typename T> void Queue<T>::insert(const T& t, Queue<T>::iterator i) { //inserts before
	if(i == nullptr) throw std::invalid_argument("null iterator");
	auto cur = i.prev_el.lock();
	cur->next =
		std::make_shared<QueueEl<T>>(t, cur->next);
	if(cur == end_el) end_el = cur->next;
	++size;
}
template <typename T> void Queue<T>::erase(iterator i) {
	if(i == nullptr) throw std::invalid_argument("null iterator");
	auto cur = i.prev_el.lock();
	if(cur->next == end_el) end_el = cur;
	cur->next = cur->next->next;
	--size;
}
template <typename T> T Queue<T>::pop() {
	if(zero_el->next == nullptr) throw std::out_of_range("empty queue");
	T element = *(begin());
	erase(begin());
	return element;
}
template <typename T> void Queue<T>::push(const T& el) {
	insert(el, begin());
}
template <typename T> T Queue<T>::top() /*const*/{
	if(zero_el->next == nullptr) throw std::out_of_range("empty queue");
	T el = *(begin());
	return el;
}
template <typename T> std::ostream& operator<<(std::ostream& cout, Queue<T>& queue) {
    for(auto i = queue.begin(); i != queue.end(); ++i) {
        cout << *i << '\n';
    }
    return cout;
}

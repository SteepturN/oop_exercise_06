#include "../header/Queue.h"
#include "../header/QueueEl.h"
#include "../header/iterator.h"
#include <memory>
template <typename T> Queue<T>::iterator::iterator()
	: prev_el(std::shared_ptr<QueueEl<T>>(nullptr)) {}
template <typename T>
typename Queue<T>::iterator& Queue<T>::iterator::operator++() {
	if(!prev_el.expired())
		prev_el = prev_el.lock()->next;
	else {
		throw std::bad_weak_ptr();
	}
	return *this;
}
template <typename T> Queue<T>::iterator::iterator(std::shared_ptr<QueueEl<T>> el)
	: prev_el(el) {}
template <typename T> bool Queue<T>::iterator::operator!=(Queue<T>::iterator iter) {
	if(iter.prev_el.lock() == nullptr || prev_el.lock() == nullptr)
		throw std::bad_weak_ptr();
	return (prev_el.lock()->next != iter.prev_el.lock()->next);
} //should I compare queues?
template <typename T> T& Queue<T>::iterator::operator*() {
	if(!prev_el.expired()) {
		std::shared_ptr<QueueEl<T>> prev = prev_el.lock();
		if(prev->next == NULL)
			throw std::out_of_range("iterator out of range");
		else return prev->next->val;
	} else throw std::bad_weak_ptr();
}
template <typename T> bool Queue<T>::iterator::operator==(iterator iter) {
	return !(*this != iter);
}
template <typename T> bool Queue<T>::iterator::operator==(std::nullptr_t) {
	return (prev_el.lock() == nullptr);
}

#include "../header/Queue.h"
#include "../header/QueueEl.h"
#include "../header/iterator.h"
#include <memory>
template <typename T, typename Alloc> Queue<T, Alloc>::iterator::iterator()
	: prev_el(std::shared_ptr<QueueEl<T>>(nullptr)) {}
template <typename T, typename Alloc>
typename Queue<T, Alloc>::iterator& Queue<T, Alloc>::iterator::operator++() {
	if(!prev_el.expired())
		prev_el = prev_el.lock()->next;
	else {
		throw std::bad_weak_ptr();
	}
	return *this;
}
template <typename T, typename Alloc>
Queue<T, Alloc>::iterator::iterator(std::shared_ptr<QueueEl<T>> el)
	: prev_el(el) {}
template <typename T, typename Alloc>
bool Queue<T, Alloc>::iterator::operator!=(Queue<T, Alloc>::iterator iter) {
	if(iter.prev_el.lock() == nullptr || prev_el.lock() == nullptr)
		throw std::bad_weak_ptr();
	return (prev_el.lock()->next != iter.prev_el.lock()->next);
} //should I compare queues?
template <typename T, typename Alloc>
T& Queue<T, Alloc>::iterator::operator*() {
	if(!prev_el.expired()) {
		std::shared_ptr<QueueEl<T>> prev = prev_el.lock();
		if(prev->next == NULL)
			throw std::out_of_range("iterator out of range");
		else return prev->next->val;
	} else throw std::bad_weak_ptr();
}
template <typename T, typename Alloc>
bool Queue<T, Alloc>::iterator::operator==(iterator iter) {
	return !(*this != iter);
}
template <typename T, typename Alloc>
bool Queue<T, Alloc>::iterator::operator==(std::nullptr_t) {
	return (prev_el.lock() == nullptr);
}
#include "../template/Queue.tpp"

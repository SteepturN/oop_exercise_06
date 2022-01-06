#include "../header/Allocator.hpp"
#include <type_traits>
#include <typeinfo>
#include <string>
template <typename T, int Size>
Allocator<T,Size>::~Allocator(){
	std::cout <<"Allocator destroyed with size = " << Size << " and type = " << typeid(T).name() <<'\n';
}

template <typename T, int Size>
Allocator<T, Size>::Allocator() :
	storage(new char[sizeof(T) * Size]), free_elements(new std::stack<T*>) {
	std::cout <<"Allocator() used with Size = " << Size << " and type = " << typeid(T).name() <<'\n';
	if(storage == nullptr) throw std::runtime_error("can't allocate storage");
	if(free_elements == nullptr) throw std::bad_alloc();
	for(int i = 0; i < Size; i++) {
		free_elements->push(reinterpret_cast<T*>(
			                    static_cast<char*>(storage.get()) + i * sizeof(T)));
	}
}
template<class T, int Size> template<class U, int Size2> Allocator<T, Size>::Allocator(const Allocator<U, Size2>&) :
	storage(new char[sizeof(T) * Size]), free_elements(new std::stack<T*>) {
	std::cout << "Allocator<T,Size>(Allocator<U,Size2>) used with Size = " << Size << " and size of type = " << typeid(T).name() <<'\n';
	std::cout << "and Size2 = " <<Size2 <<" and size of type U = " << typeid(U).name() <<'\n';
	if(storage == nullptr) throw std::runtime_error("can't allocate storage");
	if(free_elements == nullptr) throw std::bad_alloc();
	for(int i = 0; i < Size; i++) {
		free_elements->push(reinterpret_cast<T*>(
			                    static_cast<char*>(storage.get()) + i * sizeof(T)));
	}
}
template <typename T, int Size>
T* Allocator<T, Size>::allocate(int n) {
	std::cout << "allocate(" << n << ") used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	if(n != 1 || free_elements->empty()) return nullptr;
	T* ret = free_elements->top();
	free_elements->pop();
	return ret;
}
template <typename T, int Size>
void Allocator<T, Size>::deallocate(T* p, int) {
//	std::cout << "deallocate(" << p << ") used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	free_elements->push(p);
}
template<class T1, int Sz1, class T2, int Sz2>
bool operator==(const Allocator<T1, Sz1>& lhs, const Allocator<T2, Sz2>& rhs) {
//	std::cout << "operator==(" << sizeof(T1) <<' '<<Sz1 << ' ' <<sizeof(T2) << ' ' << Sz2 << ")\n";
	return ((Sz1 == Sz2) && (rhs.storage == lhs.storage)
	        && (rhs.free_elements == lhs.free_elements));
}

#include "../template/Allocator.tpp"

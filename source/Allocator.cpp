#include "../header/Allocator.hpp"
#include <type_traits>
#include <typeinfo>
#include <string>
Block::Block(size_t size, void* memory)
	: size(size), memory(memory) {}
template <typename T, int Size>
Allocator<T,Size>::~Allocator(){
//	std::cout <<"Allocator destroyed with size = " << Size << " and type = " << sizeof(T) <<'\n';
}

template <typename T, int Size>
Allocator<T, Size>::Allocator() :
	storage(new char[Size*1024]), free_elements(new std::stack<Block>) {
//	std::cout <<"Allocator() used with Size = " << Size << " and type = " << sizeof(T) <<'\n';
	if(storage == nullptr) throw std::runtime_error("can't allocate storage");
	if(free_elements == nullptr) throw std::bad_alloc();
	free_elements->push(Block(Size*1024, static_cast<void*>(storage.get())));
}
template<class T, int Size> template<class U, int Size2> Allocator<T, Size>::Allocator(const Allocator<U, Size2>& all) :
	storage(all.storage), free_elements(all.free_elements) {
//	std::cout << "Allocator<T,Size>(Allocator<U,Size2>) used with Size = " << Size << " and size of type = " << sizeof(T) <<'\n';
//	std::cout << "and Size2 = " <<Size2 <<" and size of type U = " << sizeof(U) <<'\n';
	if(storage == nullptr) throw std::runtime_error("can't allocate storage");
	if(free_elements == nullptr) throw std::bad_alloc();
}
template <typename T, int Size>
T* Allocator<T, Size>::allocate(int n) {
//	std::cout << "allocate(" << n << ") used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	if(n != 1 || free_elements->empty()) return nullptr;
	char* allocated_memory = nullptr;
	bool found = false;
	while(!found) {
		Block block = free_elements->top();
		free_elements->pop();
		if(block.size > sizeof(T)) {
			allocated_memory = static_cast<char*>(block.memory);
			free_elements->push(Block(block.size-sizeof(T), static_cast<char*>(block.memory+sizeof(T))));
			found = true;
		} else if (block.size == sizeof(T)) {
			allocated_memory = static_cast<char*>(block.memory);
			found = true;
		} else if (free_elements->size() == 0) {
			throw std::bad_alloc();
		}
	}
	return reinterpret_cast<T*>(allocated_memory);
}
template <typename T, int Size>
void Allocator<T, Size>::deallocate(T* p, int n) {
//	std::cout << "deallocate(" << p << ") used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	free_elements->push(Block(n, static_cast<void*>(p)));
}
template<class T1, int Sz1, class T2, int Sz2>
bool operator==(const Allocator<T1, Sz1>& lhs, const Allocator<T2, Sz2>& rhs) {
//	std::cout << "operator==(" << sizeof(T1) <<' '<<Sz1 << ' ' <<sizeof(T2) << ' ' << Sz2 << ")\n";
	return ((Sz1 == Sz2) && (rhs.storage == lhs.storage)
	        && (rhs.free_elements == lhs.free_elements));
}

#include "../template/Allocator.tpp"

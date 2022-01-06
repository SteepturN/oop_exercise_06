//	using const_pointer = const T*;
#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
#include <iostream>
#include <stack>
#include <memory>
template <typename T, int Size>
struct Allocator {
	using value_type = T;
	template <typename U>
	struct rebind {
		using other = Allocator<U, Size>;
	};

	Allocator();
	~Allocator();
	template <typename U, int Size2>
	Allocator(Allocator<U, Size2> const&);

	[[nodiscard]] T* allocate(int);
	void deallocate(T*, int);
	inline constexpr std::size_t max_size() const noexcept {return 1;}
//stupid task == stupid allocator
	std::shared_ptr<char[]> storage;
	std::shared_ptr<std::stack<T*>> free_elements;
};
template<class T1, int Sz1, class T2, int Sz2>
bool operator==(const Allocator<T1, Sz1>& lhs, const Allocator<T2, Sz2>& rhs);
#endif // ALLOCATOR_H_

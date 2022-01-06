#include <memory>
#include <stack>

//	using const_pointer = const T*;
#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_//	using const_pointer = const T*;
#include <iostream>
#include <stack>
#include <memory>
template <typename T, int Size>
struct Allocator {
	// using pointer = T*;
//	using void_pointer = std::nullptr_t;
//	using const_void_pointer = const std::nullptr_t;
	using value_type = T;
	// using size_type = std::size_t;
	// using difference_type = std::ptrdiff_t;
	template <typename U>
	struct rebind {
		using other = Allocator<U, Size>;
	};

	Allocator();
	//Allocator(Allocator<T, Size>& rhs);
	~Allocator();
	//Allocator(Allocator<T, Size>&& rhs);
	template <typename U, int Size2>
	Allocator(Allocator<U, Size2> const&);

	[[nodiscard]] T* allocate(int);
	void deallocate(T*, int);
	template <typename ...Args>
	inline void construct(T* p, Args... args) {new (p) T(std::forward<Args>(args)...);}
	inline constexpr std::size_t max_size() const noexcept {return 1;}
//stupid task == stupid allocator
//	bool operator!=(Allocator<T, Size> rhs);

	std::shared_ptr<char[]> storage;
	std::shared_ptr<std::stack<T*>> free_elements;
};
template<class T1, int Sz1, class T2, int Sz2>
bool operator==(const Allocator<T1, Sz1>& lhs, const Allocator<T2, Sz2>& rhs);

#endif // ALLOCATOR_H_
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
#ifndef LISTEL_H_
#define LISTEL_H_
#include <memory>
#include "../header/Rhomb.h"
template<typename T>
class QueueEl {
public:
	QueueEl(const T& val, const std::shared_ptr<QueueEl>& next);
	T val;
	std::shared_ptr<QueueEl> next;
};
#endif // LISTEL_H_

#ifndef READ_INPUT_H_
#define READ_INPUT_H_
#include <set>
#include <string>
typedef enum {
	END_OF_FILE,
	VALID_INPUT,
	INVALID_INPUT,
	END_OF_LINE,
} read_return_t;

read_return_t get_command(std::set<std::string>&, char*);
template <typename T>
read_return_t get_value(T&);
template <>
read_return_t get_value (unsigned int&);
template <>
read_return_t get_value (unsigned long long&);


#endif // READ_INPUT_H_
#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>
#include <utility>
#include <iostream>
#include <cmath>
#define NUM_OF_VERTECES 4

template <typename T>
class Rhomb;

template <typename T>
std::ostream& operator<<(std::ostream& cout, const Rhomb<T>& t);
template <typename T>
std::istream& operator>>(std::istream& cin, Rhomb<T>& t);



template <typename T>
class Rhomb {
public:
	std::vector<std::pair<T, T>> verteces;
	Rhomb(const Rhomb<T>& t);
	Rhomb();
	std::pair<double, double> center() const noexcept;
	void coordinates() const noexcept;
	double area() const noexcept;
	Rhomb<T>& operator=(const Rhomb<T>& t) noexcept;
	bool operator==(const Rhomb<T>& t) const noexcept;
	friend std::ostream& operator<< <>(std::ostream& cout, const Rhomb<T>& t);
	friend std::istream& operator>> <>(std::istream& cin, Rhomb<T>& t);
};

//#include "../template/Rhomb.tpp"

#endif // SQUARE_H_

#ifndef ITERATOR_H_
#define ITERATOR_H_
#include "../header/QueueEl.h"
#include "../header/Queue.h"
#include "../header/Rhomb.h"
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

template class Queue<Rhomb<int>>::iterator;
#endif // ITERATOR_H_

#include "../header/Allocator.hpp"
template <typename T, int Size>
Allocator<T,Size>::~Allocator(){
	std::cout <<"Allocator destroyed with size = " << Size << " and size of type = " << sizeof(T) <<'\n';
}

template <typename T, int Size>
Allocator<T, Size>::Allocator() :
	storage(new char[sizeof(T) * Size]), free_elements(new std::stack<T*>) {
	std::cout <<"Allocator() used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	for(int i = 0; i < Size; i++) {
		free_elements->push(reinterpret_cast<T*>(
			                    static_cast<char*>(storage.get()) + i * sizeof(T)));
	}
}
template<class T, int Size> template<class U, int Size2> Allocator<T, Size>::Allocator(const Allocator<U, Size2>&) :
	storage(new char[sizeof(T) * Size]), free_elements(new std::stack<T*>) {
	std::cout <<"Allocator<T,Size>(Allocator<U,Size2>) used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	std::cout << "and Size2 = " <<Size2 <<" and size of type U = " << sizeof(U) <<'\n';
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
	std::cout << "deallocate(" << p << ") used with Size = " << Size << " and size of type = " <<sizeof(T) <<'\n';
	free_elements->push(p);
}
template<class T1, int Sz1, class T2, int Sz2>
bool operator==(const Allocator<T1, Sz1>& lhs, const Allocator<T2, Sz2>& rhs) {
	std::cout << "operator==(" << sizeof(T1) <<' '<<Sz1 << ' ' <<sizeof(T2) << ' ' << Sz2 << ")\n";
	return ((Sz1 == Sz2) && (rhs.storage == lhs.storage)
	        && (rhs.free_elements == lhs.free_elements));
}

#include "../template/Allocator.tpp"
#include "../header/Rhomb.h"
#include "../header/Queue.h"
#include "../header/QueueEl.h"
#include "../header/iterator.h"
#include "../header/Allocator.hpp"
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
#include "../header/QueueEl.h"
#include "../header/Rhomb.h"
template<typename T>
QueueEl<T>::QueueEl(const T& val, const std::shared_ptr<QueueEl>& next)
	: val(val), next(next){}

#include "../template/QueueEl.tpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <set>
#include "../header/Read_input.hpp"
#include "../header/Rhomb.h"
#include "../header/Queue.h"

read_return_t get_command(std::set<std::string>& valid_commands, char* command)
{
	char ch(' ');
	while((ch == '\t') || (ch == ' ')) {
		std::cin >> ch;
		if(std::cin.eof()) exit(0);
		if(ch == '\n') ch = ' ';
	}
	std::cin.unget();
	std::cin >> command;
	if(std::cin.fail()) {
		std::cin.clear();
		return INVALID_INPUT;
	}
	if(valid_commands.count(command)) return VALID_INPUT;
	else return INVALID_INPUT;
}

template <typename T>
read_return_t get_value(T& d)
{
	char ch(' ');
	while((ch == '\t') || (ch == ' ')) {
		std::cin >> ch;
		if(std::cin.eof()) exit(0);
		if(ch == '\n') ch = ' ';
	}
	std::cin.unget();
	std::cin >> d;
	if(std::cin.fail()) {
		std::cin.clear();
		return INVALID_INPUT;
	}
	return VALID_INPUT;
}
template <>
read_return_t get_value (unsigned int& d) {
	char ch(' ');
	while((ch == '\t') || (ch == ' ')) {
		std::cin >> ch;
		if(std::cin.eof()) exit(0);
		if(ch == '\n') ch = ' ';
	}
	std::cin.unget();
	if(ch == '-') return INVALID_INPUT;
	std::cin >> d;
	if(std::cin.fail()) {
		std::cin.clear();
		return INVALID_INPUT;
	}
	return VALID_INPUT;
}
template <>
read_return_t get_value (unsigned long long& d) {
	char ch(' ');
	while((ch == '\t') || (ch == ' ')) {
		std::cin >> ch;
		if(std::cin.eof()) exit(0);
		if(ch == '\n') ch = ' ';
	}
	std::cin.unget();
	if(ch == '-') return INVALID_INPUT;
	std::cin >> d;
	if(std::cin.fail()) {
		std::cin.clear();
		return INVALID_INPUT;
	}
	return VALID_INPUT;
}
#include "../template/Read_input.tpp"
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

#include "../header/Rhomb.h"

template <typename T>
Rhomb<T>::Rhomb(const Rhomb<T>& obj)
	: verteces(obj.verteces) {}
template <typename T>
Rhomb<T>::Rhomb()
	: verteces(std::vector<std::pair<T, T>>(NUM_OF_VERTECES)) {}
template <typename T>
Rhomb<T>& Rhomb<T>::operator=(const Rhomb<T>& obj) noexcept {
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		verteces[i] = obj.verteces[i];
	}
	return *this;
}
template <typename T>
bool Rhomb<T>::operator==(const Rhomb<T>& obj) const noexcept{
	bool result = true;
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		if(verteces[i] != obj.verteces[i]) {
			result = false;
			break;
		}
	}
	return result;
}
template <typename T>
std::ostream& operator<<(std::ostream& cout, const Rhomb<T>& obj) {
	cout << "rhomb\nsides' length:\n";
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		auto v1 = obj.verteces[i];
		auto v2 = obj.verteces[(i + 1) % NUM_OF_VERTECES];
		cout << "side " << i << ": " << sqrt(pow(v1.first - v2.first, 2) +
		             pow(v1.second - v2.second, 2)) << '\n';
	}
	cout << "coordinates: ";
	obj.coordinates();
	return cout;
}
template <typename T>
double distance(std::pair<T, T> o1, std::pair<T, T> o2) {
	return sqrt(pow(o1.first - o2.first, 2)+pow(o1.second - o2.second, 2));
}
//«std::istream& operator>><int>(std::istream&, Rhomb<int>&)»
template <typename T>
std::istream& operator>>(std::istream& cin, Rhomb<T>& t) {
	enum {
	FIRST_AXIS = 0,
	SECOND_AXIS = 1,
    };
	char ch(' ');
	Rhomb<T> copy = t;
	for(int i = 0, cur_axis = 0; i < ( NUM_OF_VERTECES - 1 ) * 2;
	    ++i, cur_axis = (cur_axis + 1)%2) {
		while((ch == '\t') || (ch == ' ') || (ch == '\n')) {
			cin >> ch;
			if(cin.eof()) {
				t = copy;
				return cin;
			}
		}
		cin.unget();
		ch = ' ';
		if(cur_axis == FIRST_AXIS)
			cin >> t.verteces[i/2].first;
		else //(cur_axis == SECOND_AXIS)
			cin >> t.verteces[i/2].second;
		if(cin.fail()) {
			t = copy;
			return cin;
		}
	}
	if(distance(t.verteces[0], t.verteces[1]) !=
	   distance(t.verteces[1], t.verteces[2])) {
		std::cout << distance(t.verteces[0], t.verteces[1]) << ' ' <<
			distance(t.verteces[1], t.verteces[2]);
		t = copy;
		cin.setstate(std::ios_base::failbit);
		return cin;
	}
	t.verteces[3].first = t.verteces[0].first - t.verteces[1].first
		+ t.verteces[2].first;
	t.verteces[3].second = t.verteces[0].second - t.verteces[1].second
		+ t.verteces[2].second;
	return cin;
}
// template <typename T>
// void make_2_more_verteces(Rhomb<T>& t, double side_length) {
// 	double _distance = distance(t.verteces[0], t.verteces[2]);

// 	std::pair<double, double> center(
// 		( t.verteces[0].first + t.verteces[2].first) / 2.0,
// 		( t.verteces[0].second + t.verteces[2].second ) / 2.0);

// 	double alpha = std::atan(( t.verteces[2].second - t.verteces[0].second ) /
// 	                          ( t.verteces[2].first - t.verteces[0].first ));

// 	double side = sqrt(pow( side_length, 2 )
// 	                   - pow( _distance / 2.0 , 2 ));

// 	std::cout << center.first - side * sin(alpha) << ' ' << center.second + side * cos(alpha) << '+' <<
// 		center.first + side * sin(alpha) << ' ' <<
// 		center.second - side * cos(alpha);

// 	t.verteces[1] = std::make_pair<T, T>(
// 		static_cast<T>( center.first - side * sin(alpha) ),
// 		static_cast<T>( center.second + side * cos(alpha) ));
// 	t.verteces[3] = std::make_pair<T, T>(
// 		static_cast<T>(center.first + side * sin(alpha)),
// 		static_cast<T>(center.second - side * cos(alpha)));
// }
// //std::istream& operator>><int>(std::istream&, Rhomb<int>&)
// template <typename T>
// std::istream& operator>> (std::istream& cin, Rhomb<T>& t) {
// 	enum {
// 	FIRST_AXIS = 0,
// 	SECOND_AXIS = 1,
//     };
// 	char ch(' ');
// 	Rhomb<T> copy = t;
// 	for(int i = 0, cur_axis = 0; i < ( NUM_OF_VERTECES / 2 ) * 2;
// 	    ++i, cur_axis = (cur_axis + 1)%2) {
// 		while((ch == '\t') || (ch == ' ') || (ch == '\n')) {
// 			cin >> ch;
// 			if(cin.eof()) {
// 				t = copy;
// 				return cin;
// 			}
// 		}
// 		cin.unget();
// 		ch = ' ';
// 		if(cur_axis == FIRST_AXIS)
// 			cin >> t.verteces[ i / 2 ].first; //0 & 2 points
// 		else //(cur_axis == SECOND_AXIS)
// 			cin >> t.verteces[ i / 2 ].second;
// 		if(cin.fail()) {
// 			t = copy;
// 			return cin;
// 		}
// 	}
// 	t.verteces[2] = t.verteces[1];
// 	double side_length;
// 	cin >> side_length;
// 	if(cin.fail() ||
// 	   distance(t.verteces[0], t.verteces[1]) > 2 * side_length) {
// 		t = copy;
// 		return cin;
// 	}
// 	make_2_more_verteces(t, side_length);
// 	return cin;
// }

template <typename T>
std::pair<double, double> Rhomb<T>::center() const noexcept{
	std::pair<double, double> _center(0, 0);
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		_center.first+=verteces[i].first;
		_center.second+=verteces[i].second;
	_center.first/=static_cast<double>(NUM_OF_VERTECES);
	}
	_center.second/=static_cast<double>(NUM_OF_VERTECES);
	return _center;
}
template <typename T> void Rhomb<T>::coordinates() const noexcept {
	for(int i = 0; i < NUM_OF_VERTECES; ++i)
		std::cout << '(' << verteces[i].first << ", "
		          << verteces[i].second << ')';
}
template <typename T> double Rhomb<T>::area() const noexcept {
	double area = 0;
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		area +=
			verteces[ i ].first * verteces[( i + 1 ) % NUM_OF_VERTECES].second
			- verteces[( i + 1 ) % NUM_OF_VERTECES].first * verteces[ i ].second;
	}
	area /= 2.0;
	return area < 0 ? -area : area;
}

#include "../template/Rhomb.tpp"
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
#include <iostream>
#include "../header/Queue.h"
#include "../header/Rhomb.h"
#include "../header/Read_input.hpp"
#include "../header/iterator.h"
#include "../header/QueueEl.h"
#include <cstdio>
#include <set>
#include <string>
#include <algorithm>

int main(int argc, char *argv[]) {
	std::string help_message = "You can use\n\
--put rhomb: p [(point) 2 times and lenght of a side]\n\
--delete by figure number: d (number of figure)\n\
--print container: pr\n\
--print number of figures, which area is less then given: ar (area)\n\
--exit\n";
	Queue<Rhomb<int>> queue;
	char ch(' ');
	char command[20];
	std::set<std::string> valid_commands = {"p", "pr", "d", "exit", "ar"};
	std::cout << help_message;
	do {
		bool valid_input = false;
		do{
			read_return_t answer = get_command(valid_commands, command);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: valid_input = true; break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else break;
			}
		} while(!valid_input);
		std::string&& command_string = static_cast<std::string>(command);
		if(command_string == "exit") return 0;
		if(command_string == "p") {
			Rhomb<int> rhomb;
			if(get_value<Rhomb<int>>(rhomb) != VALID_INPUT)
				std::cout << "wrong input";
			else {
				queue.push(rhomb);
			}
		} else if(command_string == "pr") {
			std::for_each(queue.begin(), queue.end(), [](auto&& queue_el){
				std::cout << queue_el << std::endl;
			});
			// for(auto queue_el : queue) {
			// 	std::cout << queue_el << std::endl;
			// }
		} else if(command_string == "d") {
			unsigned int input_figure_number = 0;
			if(get_value<unsigned int>(input_figure_number) != VALID_INPUT ||
			input_figure_number >= queue.size) { //if there would be EOF
				std::cout << "wrong input";
			} else {
				bool all_done = false;
				Queue<Rhomb<int>>::iterator i = queue.begin();
				while(!all_done) {
					if(input_figure_number == 0) {
						all_done = true;
						queue.erase(i);
					} else {
						++i;
						--input_figure_number;
					}
				}
			}
		} else if(command_string == "ar"){
			unsigned int area = 0;
			if(get_value<unsigned int>(area) != VALID_INPUT)
				std::cout << "wrong input";
			else
				std::cout << std::count_if(queue.begin(), queue.end(),
				                           [area](const Rhomb<int>& r)
				                           {return r.area() < area;})
				          << std::endl;
		}
		do ch = getchar(); while((ch != '\n') && (ch != EOF));
		if(ch == EOF) return 0;
	} while(true);
	return 0;
}

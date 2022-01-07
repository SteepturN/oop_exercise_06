#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>
#include <utility>
#include <iostream>
#include <cmath>
#define NUM_OF_VERTECES 4

template <typename T>
class Square;

template <typename T>
std::ostream& operator<<(std::ostream& cout, const Square<T>& t);
template <typename T>
std::istream& operator>>(std::istream& cin, Square<T>& t);



template <typename T>
class Square {
public:
	std::vector<std::pair<T, T>> verteces;
	Square(const Square<T>& t);
	Square();
	std::pair<double, double> center() const noexcept;
	void coordinates() const noexcept;
	double area() const noexcept;
	Square<T>& operator=(const Square<T>& t) noexcept;
	bool operator==(const Square<T>& t) const noexcept;
	friend std::ostream& operator<< <>(std::ostream& cout, const Square<T>& t);
	friend std::istream& operator>> <>(std::istream& cin, Square<T>& t);
};

//#include "../template/Square.tpp"

#endif // SQUARE_H_


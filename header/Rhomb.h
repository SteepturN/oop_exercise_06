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


#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

#include "../header/Square.h"

template <typename T>
Square<T>::Square(const Square<T>& obj)
	: verteces(obj.verteces) {}
template <typename T>
Square<T>::Square()
	: verteces(std::vector<std::pair<T, T>>(NUM_OF_VERTECES)) {}
template <typename T>
Square<T>& Square<T>::operator=(const Square<T>& obj) noexcept {
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		verteces[i] = obj.verteces[i];
	}
	return *this;
}
template <typename T>
bool Square<T>::operator==(const Square<T>& obj) const noexcept{
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
std::ostream& operator<<(std::ostream& cout, const Square<T>& obj) {
	cout << "square\nsides' length:\n";
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
//«std::istream& operator>><int>(std::istream&, Square<int>&)»
template <typename T>
std::istream& operator>>(std::istream& cin, Square<T>& t) {
	enum {
	FIRST_AXIS = 0,
	SECOND_AXIS = 1,
    };
	char ch(' ');
	Square<T> copy = t;
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
	if((distance(t.verteces[0], t.verteces[1]) !=
	    distance(t.verteces[1], t.verteces[2])) ||
	   (distance(t.verteces[0], t.verteces[2])
	    != distance(t.verteces[0], t.verteces[1])*sqrt(2))){
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
// void make_2_more_verteces(Square<T>& t, double side_length) {
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
// //std::istream& operator>><int>(std::istream&, Square<int>&)
// template <typename T>
// std::istream& operator>> (std::istream& cin, Square<T>& t) {
// 	enum {
// 	FIRST_AXIS = 0,
// 	SECOND_AXIS = 1,
//     };
// 	char ch(' ');
// 	Square<T> copy = t;
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
std::pair<double, double> Square<T>::center() const noexcept{
	std::pair<double, double> _center(0, 0);
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		_center.first+=verteces[i].first;
		_center.second+=verteces[i].second;
	_center.first/=static_cast<double>(NUM_OF_VERTECES);
	}
	_center.second/=static_cast<double>(NUM_OF_VERTECES);
	return _center;
}
template <typename T> void Square<T>::coordinates() const noexcept {
	for(int i = 0; i < NUM_OF_VERTECES; ++i)
		std::cout << '(' << verteces[i].first << ", "
		          << verteces[i].second << ')';
}
template <typename T> double Square<T>::area() const noexcept {
	double area = 0;
	for(int i = 0; i < NUM_OF_VERTECES; ++i) {
		area +=
			verteces[ i ].first * verteces[( i + 1 ) % NUM_OF_VERTECES].second
			- verteces[( i + 1 ) % NUM_OF_VERTECES].first * verteces[ i ].second;
	}
	area /= 2.0;
	return area < 0 ? -area : area;
}

#include "../template/Square.tpp"

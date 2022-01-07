#pragma once
template class Square<int>;
template std::istream& operator>> <int>(std::istream&, Square<int>&);
template std::ostream& operator<< <int>(std::ostream&, const Square<int>&);
template double distance<int>(std::pair<int,int>, std::pair<int,int>);
//template void make_2_more_verteces(Square<int>& t, double side_length);

#pragma once
template class Rhomb<int>;
template std::istream& operator>> <int>(std::istream&, Rhomb<int>&);
template std::ostream& operator<< <int>(std::ostream&, const Rhomb<int>&);
template double distance<int>(std::pair<int,int>, std::pair<int,int>);
//template void make_2_more_verteces(Rhomb<int>& t, double side_length);

#pragma once
#include "../header/Allocator.hpp"
template class Queue<Square<int>, Allocator<QueueEl<Square<int>>, 10>>;
template class Queue<Square<int>, std::allocator<QueueEl<Square<int> > > >;
//template class Queue<Square<int>, Allocator<QueueEl<Square<int> >, 10> >::iterator;

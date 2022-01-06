#pragma once
#include "../header/Allocator.hpp"
template class Queue<Rhomb<int>, Allocator<QueueEl<Rhomb<int>>, 10>>;
template class Queue<Rhomb<int>, std::allocator<QueueEl<Rhomb<int> > > >;
//template class Queue<Rhomb<int>, Allocator<QueueEl<Rhomb<int> >, 10> >::iterator;

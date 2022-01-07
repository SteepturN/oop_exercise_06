#pragma once
#include <set>
#include <list>
#include "../header/Square.h"
#include "../header/QueueEl.h"
template class Allocator<int, 10>;
template class Allocator<std::_Rb_tree_node<int>, 10>;
template Allocator<std::_Rb_tree_node<int>, 10>::Allocator<int, 10>(Allocator<int, 10> const&);
template class Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>;
template Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::Allocator<int, 10>(Allocator<int, 10> const&);
template Allocator<std::_List_node<int>, 10>::Allocator<int, 10>(Allocator<int, 10> const&);
template class Allocator<std::_List_node<int>, 10>;


template class Allocator<QueueEl<Square<int> >, 10>;
template class Allocator<std::_Sp_counted_ptr_inplace<QueueEl<Square<int>>, Allocator<QueueEl<Square<int>>, 10>, (__gnu_cxx::_Lock_policy)2>, 10>;
//template Allocator<std::_Sp_counted_ptr_inplace<QueueEl<Square<int>>, Allocator<QueueEl<Square<int>>, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::Allocator<QueueEl<Square<int>>(Allocator<QueueEl<Square<int>> const&);
//std::allocator_traits<Allocator<QueueEl<Square<int> >, 10> >::construct(Allocator<QueueEl<Square<int> >, 10>&, QueueEl<Square<int> >*)’
//‘std::allocator_traits<Allocator<QueueEl<Square<int> >, 10> >::_S_construct(Allocator<QueueEl<Square<int> >, 10>&, QueueEl<Square<int> >*&)’
template Allocator<std::_Sp_counted_ptr_inplace<QueueEl<Square<int> >, Allocator<QueueEl<Square<int> >, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::Allocator<QueueEl<Square<int> >, 10>(Allocator<QueueEl<Square<int> >, 10> const&);


//std::allocator_traits<Allocator<QueueEl<Square<int> >, 10> >::construct(Allocator<QueueEl<Square<int> >, 10>&, QueueEl<Square<int> >*)
//std::allocator_traits<Allocator<QueueEl<Square<int> >, 10> >::_S_construct(Allocator<QueueEl<Square<int> >, 10>&, QueueEl<Square<int> >*&)’
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «main»:
// /home/steep/educat/tries/alloc.cpp:98: неопределённая ссылка на «Allocator<int, 10>::Allocator()»
// /usr/bin/ld: /home/steep/educat/tries/alloc.cpp:98: неопределённая ссылка на «Allocator<int, 10>::~Allocator()»
// /usr/bin/ld: /home/steep/educat/tries/alloc.cpp:98: неопределённая ссылка на «Allocator<int, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «std::set<int, std::less<int>, Allocator<int, 10> >::set(Allocator<int, 10> const&)»:
// /usr/include/c++/10/bits/stl_set.h:252: неопределённая ссылка на «Allocator<int, 10>::~Allocator()»
// /usr/bin/ld: /usr/include/c++/10/bits/stl_set.h:252: неопределённая ссылка на «Allocator<int, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «std::_Rb_tree<int, int, std::_Identity<int>, std::less<int>, Allocator<int, 10> >::_Rb_tree_impl<std::less<int>, true>::~_Rb_tree_impl()»:
// /usr/include/c++/10/bits/stl_tree.h:677: неопределённая ссылка на «Allocator<std::_Rb_tree_node<int>, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «std::_Rb_tree<int, int, std::_Identity<int>, std::less<int>, Allocator<int, 10> >::_Rb_tree(Allocator<int, 10> const&)»:
// /usr/include/c++/10/bits/stl_tree.h:951: неопределённая ссылка на «Allocator<std::_Rb_tree_node<int>, 10>::Allocator<int, 10>(Allocator<int, 10> const&)»
// /usr/bin/ld: /usr/include/c++/10/bits/stl_tree.h:951: неопределённая ссылка на «Allocator<std::_Rb_tree_node<int>, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «std::allocator_traits<Allocator<std::_Rb_tree_node<int>, 10> >::deallocate(Allocator<std::_Rb_tree_node<int>, 10>&, std::_Rb_tree_node<int>*, unsigned long)»:
// /usr/include/c++/10/bits/alloc_traits.h:341: неопределённая ссылка на «Allocator<std::_Rb_tree_node<int>, 10>::deallocate(std::_Rb_tree_node<int>*, int)»
// /usr/bin/ld: /tmp/ccw0vg9M.o: в функции «std::allocator_traits<Allocator<std::_Rb_tree_node<int>, 10> >::allocate(Allocator<std::_Rb_tree_node<int>, 10>&, unsigned long)»:
// /usr/include/c++/10/bits/alloc_traits.h:314: неопределённая ссылка на «Allocator<std::_Rb_tree_node<int>, 10>::allocate(int)»
// collect2: error: ld returned 1 exit status
// /usr/bin/ld: /tmp/cc7BCtvJ.o: в функции «std::__shared_count<(__gnu_cxx::_Lock_policy)2>::__shared_count<int, Allocator<int, 10>>(int*&, std::_Sp_alloc_shared_tag<Allocator<int, 10> >)»:
// /usr/include/c++/10/bits/shared_ptr_base.h:679: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::Allocator<int, 10>(Allocator<int, 10> const&)»
// /usr/bin/ld: /usr/include/c++/10/bits/shared_ptr_base.h:679: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::~Allocator()»
// /usr/bin/ld: /usr/include/c++/10/bits/shared_ptr_base.h:679: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::~Allocator()»
// /usr/bin/ld: /tmp/cc7BCtvJ.o: в функции «std::allocator_traits<Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10> >::allocate(Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>&, unsigned long)»:
// /usr/include/c++/10/bits/alloc_traits.h:314: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::allocate(int)»
// /usr/bin/ld: /tmp/cc7BCtvJ.o: в функции «std::allocator_traits<Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10> >::deallocate(Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>&, std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>*, unsigned long)»:
// /usr/include/c++/10/bits/alloc_traits.h:341: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::deallocate(std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>*, int)»
// /usr/bin/ld: /tmp/cc7BCtvJ.o: в функции «std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>::_M_destroy()»:
// /usr/include/c++/10/bits/shared_ptr_base.h:567: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::Allocator<int, 10>(Allocator<int, 10> const&)»
// /usr/bin/ld: /usr/include/c++/10/bits/shared_ptr_base.h:567: неопределённая ссылка на «Allocator<std::_Sp_counted_ptr_inplace<int, Allocator<int, 10>, (__gnu_cxx::_Lock_policy)2>, 10>::~Allocator()»
// collect2: error: ld returned 1 exit status
// /usr/bin/ld: /tmp/ccX9noX7.o: в функции «std::__cxx11::list<int, Allocator<int, 10> >::list(Allocator<int, 10> const&)»:
// /usr/include/c++/10/bits/stl_list.h:684: неопределённая ссылка на «Allocator<std::_List_node<int>, 10>::Allocator<int, 10>(Allocator<int, 10> const&)»
// /usr/bin/ld: /usr/include/c++/10/bits/stl_list.h:684: неопределённая ссылка на «Allocator<std::_List_node<int>, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccX9noX7.o: в функции «std::__cxx11::_List_base<int, Allocator<int, 10> >::_List_impl::~_List_impl()»:
// /usr/include/c++/10/bits/stl_list.h:374: неопределённая ссылка на «Allocator<std::_List_node<int>, 10>::~Allocator()»
// /usr/bin/ld: /tmp/ccX9noX7.o: в функции «std::allocator_traits<Allocator<std::_List_node<int>, 10> >::deallocate(Allocator<std::_List_node<int>, 10>&, std::_List_node<int>*, unsigned long)»:
// /usr/include/c++/10/bits/alloc_traits.h:341: неопределённая ссылка на «Allocator<std::_List_node<int>, 10>::deallocate(std::_List_node<int>*, int)»
// collect2: error: ld returned 1 exit status

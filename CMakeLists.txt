cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic")
project(6lab)
add_executable(oop_exercise_06
header/Read_input.hpp
source/Allocator.cpp
header/Allocator.hpp
template/Allocator.tpp
template/Read_input.tpp
header/Square.h
template/Square.tpp
header/Queue.h
template/Queue.tpp
header/QueueEl.h
template/QueueEl.tpp
header/iterator.h
source/Read_input.cpp
source/Square.cpp
source/Queue.cpp
source/QueueEl.cpp
source/iterator.cpp
source/main.cpp
)

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

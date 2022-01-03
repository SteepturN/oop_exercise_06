#ifndef READ_INPUT_H_
#define READ_INPUT_H_
#include <set>
#include <string>
typedef enum {
	END_OF_FILE,
	VALID_INPUT,
	INVALID_INPUT,
	END_OF_LINE,
} read_return_t;

read_return_t get_command(std::set<std::string>&, char*);
template <typename T>
read_return_t get_value(T&);
template <>
read_return_t get_value (unsigned int&);
template <>
read_return_t get_value (unsigned long long&);


#endif // READ_INPUT_H_

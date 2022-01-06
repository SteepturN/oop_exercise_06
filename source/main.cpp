#include <iostream>
#include "../header/Queue.h"
#include "../header/Rhomb.h"
#include "../header/Read_input.hpp"
#include "../header/iterator.h"
#include "../header/QueueEl.h"
#include "../header/Allocator.hpp"
#include <cstdio>
#include <set>
#include <string>
#include <algorithm>

int main(int argc, char *argv[]) {
	std::string help_message = "You can use\n\
--put rhomb: p [(point) 2 times and lenght of a side]\n\
--delete by figure number: d (number of figure)\n\
--print container: pr\n\
--print number of figures, which area is less then given: ar (area)\n\
--exit\n";
	Queue<Rhomb<int>, Allocator<QueueEl<Rhomb<int>>, 10>> queue;
	char ch(' ');
	char command[20];
	std::set<std::string> valid_commands = {"p", "pr", "d", "exit", "ar"};
	std::cout << help_message;
	do {
		bool valid_input = false;
		do{
			read_return_t answer = get_command(valid_commands, command);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: valid_input = true; break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else break;
			}
		} while(!valid_input);
		std::string&& command_string = static_cast<std::string>(command);
		if(command_string == "exit") return 0;
		if(command_string == "p") {
			Rhomb<int> rhomb;
			if(get_value<Rhomb<int>>(rhomb) != VALID_INPUT)
				std::cout << "wrong input";
			else {
				queue.push(rhomb);
			}
		} else if(command_string == "pr") {
			std::for_each(queue.begin(), queue.end(), [](auto&& queue_el){
				std::cout << queue_el << std::endl;
			});
			// for(auto queue_el : queue) {
			// 	std::cout << queue_el << std::endl;
			// }
		} else if(command_string == "d") {
			unsigned int input_figure_number = 0;
			if(get_value<unsigned int>(input_figure_number) != VALID_INPUT ||
			input_figure_number >= queue.size) { //if there would be EOF
				std::cout << "wrong input";
			} else {
				bool all_done = false;
				auto i = queue.begin();
				while(!all_done) {
					if(input_figure_number == 0) {
						all_done = true;
						queue.erase(i);
					} else {
						++i;
						--input_figure_number;
					}
				}
			}
		} else if(command_string == "ar"){
			unsigned int area = 0;
			if(get_value<unsigned int>(area) != VALID_INPUT)
				std::cout << "wrong input";
			else
				std::cout << std::count_if(queue.begin(), queue.end(),
				                           [area](const Rhomb<int>& r)
				                           {return r.area() < area;})
				          << std::endl;
		}
		do ch = getchar(); while((ch != '\n') && (ch != EOF));
		if(ch == EOF) return 0;
	} while(true);
	return 0;
}

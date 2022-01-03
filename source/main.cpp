/*
Разработать шаблоны классов согласно варианту задания.
Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат.
Классы должны иметь публичные поля. Фигуры являются фигурами вращения (правильные многоугольники),
т.е. равносторонними (кроме трапеции и прямоугольника). Для хранения координат фигур необходимо использовать шаблон  std::pair.
Например:
template <class T>
struct Rhomb {
    using vertex_t = std::pair<T,T>;
    vertex_t a,b,c,d;
};

 Создать шаблон динамической коллекциu, согласно варианту задания:
1. Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr;
2. В качестве параметра шаблона коллекция должна принимать тип данных - фигуры;
3. Реализовать forward_iterator по коллекции;
4. Коллекция должны возвращать итераторы begin() и  end();
5. Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
6. Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
7. При выполнении недопустимых операций (например выход за границы коллекции или удаление несуществующего элемента) необходимо генерировать исключения;
8. Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
9.       Коллекция должна содержать метод доступа:
стек – pop, push, top;
очередь – pop, push, top;
список, Динамический массив – доступ к элементу по оператору [].

10.     Реализовать программу, которая:
позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
позволяет удалять элемент из коллекции по номеру элемента;
выводит на экран введенные фигуры c помощью std::for_each;
выводит на экран количество объектов, у которых площадь меньше   заданной (с помощью  std::count_if).

variant: 5. Ромб, Стек
*/

#include <iostream>
#include "../header/Queue.h"
#include "../header/Rhomb.h"
#include "../header/Read_input.hpp"
#include "../header/iterator.h"
#include "../header/QueueEl.h"
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
	Queue<Rhomb<int>> queue;
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
			for(auto queue_el : queue) {
				std::cout << queue_el << std::endl;
			}
		} else if(command_string == "d") {
			unsigned int input_figure_number = 0;
			if(get_value<unsigned int>(input_figure_number) != VALID_INPUT ||
			input_figure_number >= queue.size) { //if there would be EOF
				std::cout << "wrong input";
			} else {
				bool all_done = false;
				Queue<Rhomb<int>>::iterator i = queue.begin();
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

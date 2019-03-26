#include <cstdlib>
#include <iostream>
#include <string>

int main(int /*argc*/, char* /*argv*/[])
{
	std::string command;
	std::cout << ':';
	while (std::getline(std::cin, command)) {
		if (command == "exit")
			break;
		int cmd_status = std::system(command.c_str());
		std::cout << '[' << cmd_status << ']' << ':';
	}
}

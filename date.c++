#include <chrono>
#include <iostream>

int main(int /*argc*/, char* /*argv*/[])
{
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::ctime(&t);
}

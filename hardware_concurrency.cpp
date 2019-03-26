#include <iostream>
#include <thread>

int main(int, char*[])
{
	std::cout << std::thread::hardware_concurrency() << '\n';
}

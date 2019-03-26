#include <chrono>
#include <string>
#include <thread>

int main(int argc, char *argv[])
{
	std::this_thread::sleep_for(std::chrono::seconds((argc > 1) ?
				std::stoi(argv[1]) : 1));
}

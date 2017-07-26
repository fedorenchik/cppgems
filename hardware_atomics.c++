#include <atomic>
#include <iostream>

int main(int, char*[])
{
	std::cout << "Your environment "
		<< ((std::atomic<int>(1).is_lock_free()) ?
		"supports " : "does not support ")
		<< "hardware atomic operations (for int).\n";
}

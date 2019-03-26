#include <iostream>
#include <locale>

int main(int, char*[])
{
	std::cout << "Current locale name is: " << std::locale("").name()
		<< '\n';
}

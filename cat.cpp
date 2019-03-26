#include <iostream>
#include <iterator>
#include <algorithm>

int main(int /*argc*/, char* /*argv*/[])
{
	std::noskipws(std::cin);
	std::copy(std::istream_iterator<char>(std::cin),
			std::istream_iterator<char>(),
			std::ostream_iterator<char>(std::cout, ""));
}

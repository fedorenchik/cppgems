#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

int main(int argc, char* argv[])
{
	std::noskipws(std::cin);
	std::for_each(std::istream_iterator<char>(std::cin),
			std::istream_iterator<char>(),
			[&] (const char& c) {
				std::cout << c;
				static std::ofstream out_file((argc > 1) ? argv[1] : "tee.out");
				out_file << c;
			});
}

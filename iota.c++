#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main(int argc, char *argv[])
{
	int el_num = (argc > 1) ? stoi(std::string{argv[1]}) : 10;
	std::vector<int> elements(el_num);
	std::iota(elements.begin(), elements.end(), 1);
	std::copy(elements.cbegin(), elements.cend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
}

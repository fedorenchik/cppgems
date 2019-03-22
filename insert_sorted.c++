#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
void insert_sorted(std::vector<T>& v, const T& t)
{
	const auto insert_pos{std::lower_bound(std::begin(v), std::end(v), t)};
	v.insert(insert_pos, t);
}

int main()
{
	std::vector<std::string> v {"some", "random", "strings", "in",
		"arbitrary", "order"};

	assert(!std::is_sorted(std::begin(v), std::end(v)));
	std::sort(std::begin(v), std::end(v));
	assert(std::is_sorted(std::begin(v), std::end(v)));

	insert_sorted(v, std::string{"test"});
	insert_sorted(v, std::string{"sorted"});

	for (const auto &e : v) {
		std::cout << e << " ";
	}
	std::cout << '\n';
}

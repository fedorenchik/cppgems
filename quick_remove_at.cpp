/*
 * Remove element from unsorted vector in O(1) time.
 */
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void quick_remove_at(std::vector<T>& v, std::size_t idx)
{
	if (idx < v.size()) {
		v.at(idx) = std::move(v.back());
		v.pop_back();
	}
}

template <typename T>
void quick_remove_at(std::vector<T>& v, typename std::vector<T>::iterator it)
{
	if (it != std::end(v)) {
		*it = std::move(v.back());
		v.pop_back();
	}
}

int main()
{
	std::vector<int> v {53, 62, 34, 39, 76};

	quick_remove_at(v, 2);

	for (int i : v) {
		std::cout << i << ", ";
	}
	std::cout << '\n';

	quick_remove_at(v, std::find(std::begin(v), std::end(v), 53));

	for (int i : v) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}

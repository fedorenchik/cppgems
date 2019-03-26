#include <iostream>
#include <functional>
#include <list>
#include <map>

struct billionaire {

	std::string name;
	double dollars;
	std::string country;
};

int main()
{
	std::list<billionaire> billionaires {
		{"Bill Gates", 86.0, "USA"},
		{"Warren Buffet", 75.6, "USA"},
	};

	std::map<std::string, std::pair<const billionaire, size_t>> m;

	for (const auto& b : billionaires) {
		auto [iterator, success] = m.try_emplace(b.country, b, 1);

		if (!success) {
			++iterator->second.second;
		}
	}

	for (const auto& [key, value] : m) {
		const auto& [b, count] = value;

		std::cout << b.country << " : " << count
			<< "billionaires. Richest is " << b.name << " with "
			<< b.dollars << " B$\n";
	}
}

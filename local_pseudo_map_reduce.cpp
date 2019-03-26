#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

struct Record {
	int price;
};

std::ostream& operator<<(std::ostream& out, const Record& rec)
{
	return out << "[ Price: " << rec.price << " ] ";
}

std::vector<Record> goods{};	// data to be searched

void gen_random_records()
{
	std::random_device rand_dev;
	std::default_random_engine rand_eng(rand_dev());
	std::uniform_int_distribution<int> rand_distr(1, 1'000'000'000);
	for (int i = 0; i < 1'000'000'000; ++i) {
		Record r;
		r.price = rand_distr(rand_eng);
		goods.push_back(r);
	}
}

const int grain = 50'000'000;

/**
 * Wait until every future in args has a value.
 */
template<typename T>
std::vector<T> wait_for_all(std::vector<std::future<T>>& vf)
{
	std::vector<T> res;
	for (auto& fu : vf)
		res.push_back(fu.get());
	return res;
}

/**
 * Wait until one future in args has a value.
 * Return index of ready future.
 * If no future is ready, wait for d before trying again.
 */
template<typename T>
int wait_for_any(std::vector<std::future<T>>& vf,
		std::chrono::steady_clock::duration d)
{
	while (true) {
		for (int i = 0; i != vf.size(); ++i) {
			if (!vf[i].valid())
				continue;
			switch (vf[i].wait_for(std::chrono::seconds{0})) {
			case std::future_status::ready:
				return i;
			case std::future_status::timeout:
				break;
			case std::future_status::deferred:
				throw std::runtime_error("wait_for_any(): deferred future");
			}
		}
		std::this_thread::sleep_for(d);
	}
}

template<typename Pred>
std::vector<Record*> find_all_rec(std::vector<Record>& vr,
		int first, int last, Pred pr)
{
	std::vector<Record*> res;
	for (int i = first; i != last; ++i)
		if (pr(vr[i]))
			res.push_back(&vr[i]);
	return res;
}

template<typename Pred>
std::vector<Record*> pfind_all(std::vector<Record>& vr, Pred pr)
{
	std::vector<std::future<std::vector<Record*>>> res;

	for (size_t i = 0; i != vr.size(); i += grain)
		res.push_back(std::async(find_all_rec<Pred>, std::ref(vr),
					i, i + grain, pr));

	std::vector<std::vector<Record*>> r2 = wait_for_all(res);

	std::vector<Record*> r;
	for (auto& x : r2)
		for (auto p : x)
			r.push_back(p);
	return r;
}

void find_all_cheap_red()
{
	assert(goods.size() % grain == 0);

	auto vp = pfind_all(goods,
			[] (Record& r) { return r.price < 200; });
	for (auto p : vp)
		std::cout << "record " << *p << '\n';
}

int main()
{
	gen_random_records();
	std::cerr << "start find\n";
	find_all_cheap_red();
}

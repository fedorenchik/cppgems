#include <thread>

namespace ext {

class guarded_thread : public std::thread {
public:
	using std::thread::thread;
	~guarded_thread() { if (this->joinable()) this->join(); }
};

}

int main()
{
	ext::guarded_thread t1;
	ext::guarded_thread t2;
}

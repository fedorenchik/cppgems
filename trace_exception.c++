#include <exception>
#include <execinfo.h>
#include <iostream>
#include <string>

namespace ext {

const int MAX_TRACES = 20;

class trace {
public:
	trace() {
		void* cur_trace[MAX_TRACES];
		int trace_size = backtrace(cur_trace, MAX_TRACES);
		char** trace_symbols = backtrace_symbols(cur_trace, trace_size);
		for (int i = 0; i < trace_size; ++i) {
			call_trace_ += std::string{trace_symbols[i]} + '\n';
		}
		std::free(trace_symbols);
	}
	std::string call_trace() const {
		return call_trace_;
	}
private:
	std::string call_trace_;
};

}

namespace ext {

class trace_exception : public std::exception, public ext::trace {
};

}

int f()
{
	throw ext::trace_exception{};
}

void g()
{
	try {
		f();
	} catch(const std::exception& e) {
		std::cerr << "Can be caught by std::exception.\n";
		throw;
	}
}

int main()
try {
	g();
} catch (const ext::trace_exception& e) {
	std::cerr << "Call Trace:\n" << e.call_trace();
} catch (...) {
	std::cerr << "Unknown exception caught.\n";
}

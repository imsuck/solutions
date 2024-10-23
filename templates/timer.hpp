#include <chrono>
using namespace std;
using namespace chrono;

#if false
struct Timer {
    string _msg;
    time_point<steady_clock> start = steady_clock::now(), end;
    void stop() { end = steady_clock::now(); }
    Timer() = default;
    Timer(const string &msg) : _msg(msg + ": ") {}
    ~Timer() {
    #ifdef LOCAL
        stop(), cerr << _msg << (end - start) / 1ms << "ms\n";
    #endif
    }
};
#endif

#if true
template<class Fn> struct Timer {
    Fn fn;
    time_point<steady_clock> start = steady_clock::now(), end;
    bool done = false;
    void stop() { end = steady_clock::now(), done = true; }
    Timer(Fn f) : fn(f) {}
    void display() {
        stop();
    #ifdef LOCAL
        fn(end - start), cout << flush;
    #endif
    }
    #ifdef LOCAL
    ~Timer() {
        end = max(steady_clock::now(), end);
        if (done) return;
        fn(end - start), cout << flush;
    }
    #endif
};
#endif
template<class Fn> Timer<Fn> make_timer(const Fn &&fn) { return {fn}; }

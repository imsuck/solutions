#include <chrono>
using namespace std;
using namespace chrono;

#if true
template<class Fn> struct Timer {
    Fn fn;
    time_point<steady_clock> end, start;
    bool done = false;
    void stop() { end = steady_clock::now(), done = true; }
    Timer(Fn f) : fn(f), start(steady_clock::now()) {}
    void display() {
        stop();
    #ifdef LOCAL
        fn(end - start), cout << flush;
    #endif
    }
    #ifdef LOCAL
    ~Timer() {
        end = max(steady_clock::now(), end);
        if (done)
            return;
        fn(end - start), cout << flush;
    }
    #endif
};
#endif
template<class Fn> Timer<Fn> make_timer(const Fn &&fn) { return {fn}; }

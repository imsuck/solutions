#include <type_traits>
using namespace std;

template<class Fn> struct recur_t {
    Fn fn;
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fn(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class Fn> decltype(auto) make_recur(Fn &&f) {
    return recur_t<decay_t<Fn>>{forward<Fn>(f)};
}

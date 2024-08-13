#include <type_traits>
using namespace std;

template<class Fn> struct y_comb_res {
    Fn fn;
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fn(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class Fn> decltype(auto) y_comb(Fn &&f) {
    return y_comb_res<decay_t<Fn>>{forward<Fn>(f)};
}

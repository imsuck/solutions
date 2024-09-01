#include <type_traits>
using namespace std;

template<class F> struct y_comb_res {
    F fn;
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fn(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class F> decltype(auto) y_comb(F &&f) {
    return y_comb_res<decay_t<F>>{forward<F>(f)};
}

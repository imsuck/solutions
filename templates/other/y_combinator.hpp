#include <type_traits>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class T> y_comb_t(T &&_f) : f(forward<T>(_f)) {}
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

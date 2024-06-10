using namespace std;

// Not the exact y combinator but good enough
template<class Fn> struct add_recursion_t {
    Fn fn;
    template<class... Args> auto operator()(Args &&...args) {
        return fn(*this, args...);
    }
};
template<class Fn> auto make_recur(Fn &&f) { return add_recursion_t<Fn>{f}; }

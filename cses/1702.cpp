#include <bits/stdc++.h>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class T> y_comb_t(T &&_f) : f(forward<T>(_f)) {}
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(/* ref */ (*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;
template<class T> fn len(const T &x) -> i32 { return i32(x.size()); }

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n;
    cin >> n;
    vec<i32> pre(n), in(n), pin(n), l(n, -1), r(n, -1);
    for (i32 i = 0; i < n; i++) {
        cin >> pre[i], pre[i]--;
    }
    for (i32 i = 0; i < n; i++) {
        cin >> in[i], in[i]--;
        pin[in[i]] = i;
    }

    stack<i32> s;
    for (i32 i : pre) {
        i32 lst = -1;
        if (s.size() && pin[i] < pin[s.top()]) l[s.top()] = i;
        while (s.size() && pin[s.top()] < pin[i]) lst = s.top(), s.pop();
        if (lst != -1) r[lst] = i;
        s.push(i);
    }

    i32 t = 0;
    y_comb([&](auto &self, i32 v) -> void {
        if (v == -1) return;
        self(l[v]);
        self(r[v]);
        cout << v + 1 << " \n"[++t == n];
    })(pre[0]);
}

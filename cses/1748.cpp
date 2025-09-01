#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/compressor.hpp"
#include "library/other/types.hpp"

using mint = modint107;

template<class T> struct fenwick_tree {
    i32 n;
    vec<T> t;

    fenwick_tree(i32 _n = 0) : n(_n), t(n + 1) {}

    void add(i32 p, T d) {
        for (p++; p <= n; p += p & -p) t[p] += d;
    }
    T sum(i32 r) const {
        T s = 0;
        for (; r; r &= r - 1) s += t[r];
        return s;
    }
};

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 n;
    cin >> n;
    Compressor comp(n);
    vec<i32> a(n);
    for (i32 &i : a) cin >> i;
    comp.push(a);
    i32 m = comp.build();
    mint ans = 0;
    fenwick_tree<mint> t(m);
    for (i32 i : a) {
        mint d = t.sum(i) + 1;
        ans += d, t.add(i, d);
    }
    cout << ans << "\n";
}

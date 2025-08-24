#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto

template<class F, class I> void bin_search(I &l, I &r, F &&f) {
    while (r - l > 1) {
        I m = l + (r - l) / 2;
        (f(m) ? l : r) = m;
    }
}

fn solve() {
    i32 n, t;
    cin >> n >> t;
    vec<i32> k(n);
    for (i32 &i : k) cin >> i;
    i64 l = 0, r = 1.1e18;
    bin_search(l, r, [&](i64 x) -> bool {
        i64 s = 0;
        for (i32 i : k) {
            s += x / i;
            if (s >= t) return false;
        }
        return s < t;
    });
    cout << r << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

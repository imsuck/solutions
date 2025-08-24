#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

#define fn auto

fn solve() {
    i32 n;
    cin >> n;
    set<i32> avail;
    for (i32 i = 1; i <= n; i++) avail.insert(i);
    vec<i32> p(n);
    // number of calls: n + 1
    bool ok = y_comb([&](auto &f, i32 pos) -> bool {
        if (pos == n) return true;
        auto it = avail.begin();
        for (i32 i; it != avail.end(); it = avail.upper_bound(i)) {
            i = *it;
            if ((pos && abs(p[pos - 1] - i) < 2)) continue;
            p[pos] = i, avail.erase(i);
            if (f(pos + 1)) return true;
            avail.insert(i);
        }
        return false;
    })(0);
    if (!ok) {
        cout << "NO SOLUTION\n";
        return;
    }
    for (i32 i = 0; i < n; i++) cout << p[i] << " \n"[i == n - 1];
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/dp_cache_int.hpp"
#include "library/other/types.hpp"

void solve() {
    i64 l, r;
    cin >> l >> r;

    auto calc = [](i64 x) -> i64 {
        if (x < 0) return 0;
        vec<i32> d;
        for (; x; x /= 10) d.push_back(x % 10);
        reverse(begin(d), end(d));
        auto dp = use_cache<i64, 4>(
            {(i32)d.size() + 1, 10, 2, 2},
            [&](auto &f, i32 p, i32 dig, bool t, bool z) -> i64 {
                if (p == d.size()) return 1;
                i32 lim = t ? d[p] : 9;
                i64 acc = 0;
                for (i32 i = 0; i <= lim; i++)
                    if (i != dig || (z && !i))
                        acc += f(p + 1, i, t && i == lim, z && !i);
                return acc;
            }
        );
        return dp(0, 0, 1, 1);
    };

    cout << calc(r) - calc(l - 1) << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/dbg.hpp"
#include "library/other/ranges_util.hpp"
#include "library/other/types.hpp"

using mint = modint998;

void solve() {
    i32 n, m, k, q;
    cin >> n >> m >> k >> q;

    set<i32> row, col;
    vec<pair<i32, i32>> qs(q);
    for (auto &[x, y] : qs) cin >> y >> x;
    mint ans = 1;
    for (auto [x, y] : rev(qs)) {
        i32 ya = 0;
        if (!row.count(y)) row.insert(y), ya = 1;
        if (!col.count(x)) col.insert(x), ya = 1;
        if (ya) ans *= k;
        if (row.size() == n || col.size() == m) break;
    }
    cout << ans << "\n";
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}

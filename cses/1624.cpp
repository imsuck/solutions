#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

void solve() {
    vec<str> b(8);
    for (str &r : b) cin >> r;
    vec<i32> row(8), diag1(15), diag2(15);
    auto check = [&](i32 x, i32 y) {
        return !row[y] && !diag1[x + y] && !diag2[x - y + 7] && b[y][x] != '*';
    };
    auto add = [&](i32 x, i32 y, i32 d) {
        row[y] += d, diag1[x + y] += d, diag2[x - y + 7] += d;
    };
    i32 ans = 0;
    y_comb([&](auto &rec, i32 x) -> void {
        if (x == 8) return void(ans++);
        for (i32 y = 0; y < 8; y++) {
            if (!check(x, y)) continue;
            add(x, y, +1);
            rec(x + 1);
            add(x, y, -1);
        }
    })(0);
    cout << ans << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

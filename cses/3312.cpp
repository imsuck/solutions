#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/two_sat.hpp"
#include "library/other/types.hpp"

#define fn auto
auto _read = [](auto &&...a) { ((cin >> a), ...); };
#define rd(ty, a...) ty a; _read(a)

fn solve() {
    rd(i32, n, m);
    vec<str> b(n);
    for (str &r : b) cin >> r;
    map<char, array<char, 2>> mp{
        {'A', {'B', 'C'}},
        {'B', {'A', 'C'}},
        {'C', {'A', 'B'}},
    };
    TwoSAT sat(n * m);
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            i32 id = i * m + j, oid;
            if (i) {
                oid = id - m;
                auto x = mp[b[i][j]], y = mp[b[i - 1][j]];
                if (x[0] == y[0]) sat.add_nand(~id, ~oid);
                if (x[0] == y[1]) sat.add_nand(~id, oid);
                if (x[1] == y[0]) sat.add_nand(id, ~oid);
                if (x[1] == y[1]) sat.add_nand(id, oid);
            }
            if (j) {
                oid = id - 1;
                auto x = mp[b[i][j]], y = mp[b[i][j - 1]];
                if (x[0] == y[0]) sat.add_nand(~id, ~oid);
                if (x[0] == y[1]) sat.add_nand(~id, oid);
                if (x[1] == y[0]) sat.add_nand(id, ~oid);
                if (x[1] == y[1]) sat.add_nand(id, oid);
            }
        }
    }
    auto sol = sat.run();
    if (sol.empty()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            i32 id = i * m + j;
            cout << mp[b[i][j]][sol[id]];
        }
        cout << "\n";
    }
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
auto _read = [](auto &&...a) { ((cin >> a), ...); };
#define rd(ty, a...) ty a; _read(a)

fn solve() {
    rd(i32, n, m);
    vec<str> b(n);
    for (str &r : b) cin >> r;
    auto find_free = [](str ng) {
        for (char c : {'A', 'B', 'C', 'D'})
            if (find(begin(ng), end(ng), c) == end(ng)) return c;
        return '!';
    };
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            str ng{b[i][j]};
            if (i) ng += b[i - 1][j];
            if (j) ng += b[i][j - 1];
            b[i][j] = find_free(ng);
        }
    }
    for (str &r : b) cout << r << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

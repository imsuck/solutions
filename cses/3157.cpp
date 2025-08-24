#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

#define fn auto
using mint = modint107;

fn solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
    vector E(n + 1, vec<mint>(n + 1));

    E[1][0] = 1;
    for (i32 i = 2; i <= n; i++) {
        E[i][0] = 1;
        for (i32 j = 1; j < i; j++)
            E[i][j] = (i - j) * E[i - 1][j - 1] + (j + 1) * E[i - 1][j];
    }
    for (i32 j = 0; j < n; j++) cout << E[n][j] << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

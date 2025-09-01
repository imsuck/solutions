#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

using mint = modint107;

void solve() {
    i32 n, m;
    cin >> n >> m;
    mint ans = 0;
    for (i32 i = 0; i < n; i++) ans += mint(m).pow(gcd(i, n));
    cout << ans / n << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

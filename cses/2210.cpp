#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

using mint = modint107;
const auto mod = mint::mod();

void solve() {
    i64 n, k;
    cin >> n;
    k = n / 2;
    mint ans = 0, two = 2;
    // rot 0deg
    ans += two.pow((n * n) % (mod - 1));
    // rot 90deg/270deg
    ans += 2 * two.pow((k * k + (n & 1 ? k + 1 : 0)) % (mod - 1));
    // rot 180deg
    ans += two.pow((k * n + (n & 1 ? k + 1 : 0)) % (mod - 1));
    // dbg(two.pow((k * k) % (mod - 1)));
    cout << ans / 4 << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

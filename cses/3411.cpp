#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

using i128 = __int128_t;

ostream &operator<<(ostream &os, i128 x) {
    os << (x < 0 ? x = -x, "-" : "");
    if (x > 9) os << x / 10;
    return os << i32(x % 10);
}

void solve() {
    i32 n;
    cin >> n;
    vec<i32> x(n), y(n);
    for (i32 i = 0; i < n; i++) cin >> x[i] >> y[i];
    auto ya = [&](auto &a) {
        sort(begin(a), end(a));
        i128 ans = 0, s = accumulate(begin(a), end(a), i128(0));
        for (i32 i = 0; i < n; i++) ans += s - (i128)a[i] * (n - i), s -= a[i];
        return ans;
    };
    cout << ya(x) + ya(y) << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

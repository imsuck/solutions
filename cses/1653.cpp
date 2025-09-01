#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"

auto chmin = [](auto &a, auto &&b) { return b < a ? a = b, 1 : 0; };

const i32 N = 20;
array<i32, 2> dp[1 << N];

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 n, cap;
    cin >> n >> cap;
    vec<i32> a(n);
    for (i32 &i : a) cin >> i;

    dp[0] = {1, 0};
    for (i32 mask = 1; mask < 1 << n; mask++) {
        dp[mask] = {n + 1, cap + 1};
        for (i32 i = 0; i < n; i++) {
            if (~mask >> i & 1) continue;
            i32 sub = mask ^ 1 << i;
            auto pot = dp[sub];
            if (pot[1] > cap - a[i]) {
                pot = {pot[0] + 1, a[i]};
            } else {
                pot[1] += a[i];
            }
            chmin(dp[mask], pot);
        }
    }
    cout << dp[(1 << n) - 1][0] << "\n";
}

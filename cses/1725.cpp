#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

void solve() {
    i32 n, a, b;
    cin >> n >> a >> b;
    vec<vec<f80>> p(n + 1, vec<f80>(6 * n + 1));
    for (i32 i = 1; i <= 6; i++) p[1][i] = 1.0L / 6;
    for (i32 i = 1; i < n; i++)
        for (i32 j = i; j <= min(b, 6 * i); j++)
            for (i32 k = 1; k <= 6 && k + j <= b; k++)
                p[i + 1][j + k] += p[i][j] / 6;
    f80 ans = 0;
    for (i32 i = a; i <= b; i++) ans += p[n][i];
    cout << ans << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(6);
    solve();
}

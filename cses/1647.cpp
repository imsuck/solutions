#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;

void solve() {
    i32 n, q;
    cin >> n >> q;
    i32 w = 31 - __builtin_clz(n);
    i32 st[n + 1][w + 1];
    for (i32 i = 1; i <= n; i++) {
        cin >> st[i][0];
    }
    for (i32 j = 1; j <= w; j++) {
        for (i32 i = 1; i + (1 << (j - 1)) <= n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
    while (q--) {
        i32 l, r;
        cin >> l >> r;
        i32 k = 31 - __builtin_clz(r - l + 1);
        cout << min(st[l][k], st[r - (1 << k) + 1][k]) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

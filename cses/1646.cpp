#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i64 = int64_t;

void solve() {
    i64 n, q;
    cin >> n >> q;
    i64 a[n + 1], p[n + 1];
    p[0] = 0;
    for (i64 i = 1; i <= n; i++) {
        cin >> i[a];
        i[p] = (i - 1)[p] + i[a];
    }
    while (q--) {
        i64 l, r;
        cin >> l >> r;
        cout << r[p] - (l - 1)[p] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

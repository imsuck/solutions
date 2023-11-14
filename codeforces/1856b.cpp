#include "bits/stdc++.h"
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using i64 = int64_t;
#define vec vector

void solve() {
    i64 n, cnt_1 = 0, s = 0, x;
    cin >> n;
    for (i32 i = 0; i < n; i++) {
        cin >> x, cnt_1 += x == 1, s += x;
    }
    if (n == 1) {
        cout << "NO\n";
        return;
    }
    cout << (s - cnt_1 >= n ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

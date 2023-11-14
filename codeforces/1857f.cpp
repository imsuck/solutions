#include "bits/stdc++.h"
#include <math.h>
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

bool perf_sq(i64 n) {
    i64 sq = sqrtl(n);
    for (i64 i = max(sq - 5, i64(0)); i < sq + 5; i++) {
        if (i * i == n) {
            return true;
        }
    }
    return false;
}

void solve() {
    i32 n;
    cin >> n;
    map<i64, i64> m;
    for (i32 i = 0; i < n; i++) {
        i32 x;
        cin >> x;
        m[x]++;
    }
    i32 qq;
    cin >> qq;
    while (qq--) {
        i64 x, y;
        cin >> x >> y;
        if (x * x < 4 * y) {
            cout << "0 ";
        } else if (x * x == 4 * y) {
            i64 cnt = m[x / 2];
            cout << cnt * (cnt - 1) / 2 << " ";
        } else {
            if (!perf_sq(x * x - 4 * y)) {
                cout << "0 ";
                continue;
            }
            f128 del = sqrtl(x * x - 4 * y);
            i64 s1 = (x - i64(del)) / 2, s2 = (x + i64(del)) / 2;
            cout << m[s1] * m[s2] << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

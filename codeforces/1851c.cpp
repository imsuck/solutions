#include "bits/stdc++.h"
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

void solve() {
    i32 n, k, start = -1, end = -1, c1 = 0, c2 = 0;
    bool cnt_start = true;
    cin >> n >> k;
    i32 c[n];
    for (i32 i = 0; i < n; i++) {
        cin >> c[i];
    }
    start = c[0];
    end = c[n - 1];
    for (i32 i = 0; i < n; i++) {
        if (cnt_start && c[i] == start) {
            c1++;
            if (c1 == k) {
                cnt_start = false;
            }
        } else if (!cnt_start && c[i] == end) {
            c2++;
            if (c2 == k) {
                break;
            }
        }
    }
    if (start == end) {
        c2 = c1;
    }
    cout << ((c1 == k) && (c2 == k) ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

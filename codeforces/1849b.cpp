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
    i32 n, k;
    cin >> n >> k;
    array<i32, 2> a[n];
    for (i32 i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
        a[i][0] %= k;
        if (a[i][0] == 0) {
            a[i][0] = 1e9;
        }
    }
    sort(a, a + n, [](array<i32, 2> &a_, array<i32, 2> &b_) {
        if (a_[0] == b_[0]) {
            return a_[1] < b_[1];
        }
        return a_[0] > b_[0];
    });
    for (i32 i = 0; i < n; i++) {
        cout << a[i][1] + 1 << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

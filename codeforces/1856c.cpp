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
    vec<i32> a(n), ub(n);
    for (i32 &x : a) {
        cin >> x;
    }
    ub[n - 1] = a[n - 1];
    for (i32 i = n - 2; i >= 0; i--) {
        ub[i] = max(a[i], ub[i + 1] + 1);
    }
    for (i32 x : ub) {
        cout << x << " ";
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

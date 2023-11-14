// Overthinking...
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
    i32 n, m;
    cin >> n >> m;
    i32 left[n], right[n];
    str s;
    cin >> s;
    for (i32 i = 0; i < n; i++) {
        right[i] = (s[i] == '0' ? i : (i == 0 ? -1 : right[i - 1]));
    }
    for (i32 i = n - 1; i >= 0; i--) {
        left[i] = (s[i] == '1' ? i : (i == n - 1 ? n : left[i + 1]));
    }
    set<pair<i32, i32>> se;
    for (i32 i = 0; i < m; i++) {
        i32 l, r;
        cin >> l >> r;
        if (left[--l] >= right[--r]) {
            se.emplace(0, 0);
        } else {
            se.emplace(left[l], right[r]);
        }
    }
    cout << se.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

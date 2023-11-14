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
    i32 n;
    cin >> n;
    vec<i32> a(n + 1), b(n + 1);
    vec<pair<i32, i32>> d(n + 1);
    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (i32 i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (i32 i = 1; i <= n; i++) {
        d[i].first = a[i] - b[i];
        d[i].second = i;
    }
    sort(d.begin() + 1, d.end(),
         [](const pair<i32, i32> &a, const pair<i32, i32> &b) {
             return a.first > b.first ||
                    a.first == b.first && a.second < b.second;
         });
    i32 prev = d[1].first;
    vec<i32> ans;
    for (i32 i = 1; i <= n && d[i].first == prev; i++) {
        ans.eb(d[i].second);
    }
    cout << ans.size() << "\n";
    for (i32 i = 0; i < ans.len(); i++) {
        cout << ans[i] << " \n"[i == ans.len() - 1];
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

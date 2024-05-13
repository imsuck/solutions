#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, k;
    cin >> n >> k;
    vec<i32> v(n);
    for (i32 &i : v) {
        cin >> i;
    }
    map<i32, i32> m;
    i64 ans = 0;
    for (i32 l = 0, r = 0; r < n; r++) {
        m[v[r]]++;
        while (m.len() > k) {
            m[v[l]]--;
            if (m[v[l]] == 0) m.erase(v[l]);
            l++;
        }
        ans += r - l + 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

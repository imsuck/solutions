#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
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
#define pb push_back
#define pp pop_back
#define eb emplace_back

i32 compress(i32 a, vec<i32> &v) {
    return lower_bound(all(v), a) - v.begin();
}

void solve() {
    i32 n;
    cin >> n;
    vec<i32> a(n), b(n), p(n);
    vec<i32> val;
    for (i32 i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> p[i];
        b[i]++;
        val.pb(a[i]), val.pb(b[i]);
    }
    sort(all(val));
    val.erase(unique(all(val)), val.end());
    vec<vec<pair<i32, i32>>> projects(val.size());
    for (i32 i = 0; i < n; i++) {
        projects[compress(b[i], val)].eb(compress(a[i], val), p[i]);
    }

    vec<i64> dp(val.size(), 0);
    for (i32 i = 0; i < val.size(); i++) {
        i ? dp[i] = dp[i - 1] : 0;
        for (auto &project : projects[i]) {
            dp[i] = max(dp[i], dp[project.first] + project.second);
        }
    }
    cout << dp.back() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

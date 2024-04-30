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
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
    vec<i32> a(n);
    map<i32, i32> mp, cur;
    for (i32 &i : a) {
        cin >> i;
    }
    for (i32 i = 0; i < m; i++) {
        i32 b;
        cin >> b;
        mp[b]++;
    }
    i32 cnt = 0, ans = 0;
    for (i32 i = 0; i < m; i++) {
        cur[a[i]]++;
        if (cur[a[i]] <= mp[a[i]]) {
            cnt++;
        }
    }
    ans += cnt >= k;
    for (i32 i = 0; i + m < n; i++) {
        i32 end = i + m;
        cur[a[i]]--;
        if (cur[a[i]] < mp[a[i]]) {
            cnt--;
        }
        cur[a[end]]++;
        if (cur[a[end]] <= mp[a[end]]) {
            cnt++;
        }
        ans += cnt >= k;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

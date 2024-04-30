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
    i32 n;
    cin >> n;
    vec<pair<i32, i32>> v(n);
    vec<tuple<i32, i32, i32>> sw;
    for (i32 i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        sw.emplace_back(v[i].first, 1, i);
        sw.emplace_back(v[i].second + 1, -1, i);
    }
    sort(all(sw));
    i32 mx = 0, cur = 0;
    for (auto &p : sw) {
        cur += get<1>(p);
        mx = max(mx, cur);
    }
    cout << mx << "\n";
    set<i32> st;
    map<i32, i32> m;
    vec<i32> ans(n);
    for (i32 i = 1; i <= n; i++) st.insert(i);
    for (i32 i = 0; i < 2*n; i++) {
        i32 type, idx;
        tie(ignore, type, idx) = sw[i];
        if (type == 1) {
            i32 room = *st.begin();
            ans[idx] = room ;
            st.erase(st.begin());
            m[idx] = room;
        } else {
            st.insert(m[idx]);
        }
    }
    for (i32 i = 0; i < n; i++) cout << ans[i] << " \n"[i == n-1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

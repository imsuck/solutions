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
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, a, b;
    cin >> n >> a >> b;
    vector<i64> v(n + 1);
    for (i32 i = 1; i <= n; i++)
        cin >> v[i];
    for (i32 i = 1; i <= n; i++)
        v[i] += v[i - 1];

    i64 mx = -1e16;
    multiset<i64> ms;
    for (int i = 0; i <= n; i++) {
        if (i - b - 1 >= 0) ms.erase(ms.find(v[i - b - 1]));
        if (i - a >= 0) ms.insert(v[i - a]);
        if (!ms.empty())
            mx = mx == (i64)-1e16 ? v[i] - *ms.begin()
                                  : max(mx, v[i] - *ms.begin());
    }
    cout << mx << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

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
    str t, p;
    cin >> t >> p;
    i32 n = t.len(), m = p.len(), k = n + m + 1;
    str s = p + '$' + t;
    vec<i32> z(k);
    i32 cnt = 0;
    for (i32 i = 1, l = 0, r = 0; i < k; i++) {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        while (i + z[i] < k && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > r) 
            l = i, r = i + z[i];
        cnt += z[i] == m;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

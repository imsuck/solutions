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

bool pred(i64 x, i32 k, vec<i32> &v) {
    i64 cur = 0, cnt = 0;
    for (i32 i = 0; i < v.size(); i++) {
        if (v[i] > x)
            return false;
        if (cur > x - v[i])
            cur = 0, cnt++;
        cur += v[i];
    }
    return (cnt + (cur > 0)) <= k;
}

void solve() {
    i32 n, k;
    cin >> n >> k;
    vec<i32> v(n);
    for (i32 &i : v) {
        cin >> i;
    }

    i64 l = 1, r = 2e14;
    while (r - l > 1) {
        i64 m = (l + r) / 2;
        if (pred(m, k, v)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

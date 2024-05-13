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

bool pred(i32 f, i32 k, vec<i32> &z) {
    i32 n = z.size(), cnt = 1;
    for (i32 i = f; i < n; i++) {
        if (z[i] >= f) i += f - 1, cnt++;
    }
    return cnt >= k;
}

void solve() {
    i32 n, k;
    cin >> n >> k >> k;
    str s;
    cin >> s;
    vec<i32> z(n);
    i32 _l = 0, _r = 0;
    for (i32 i = 1; i < n; i++) {
        if (i < _r)
            z[i] = min(_r - i, z[i - _l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) 
            z[i]++;
        if (i + z[i] > _r)
            _l = i, _r = i + z[i];
    }
    i32 l = 1, r = n / k + 1;
    // dbg(z);
    // dbg(pred(3, 2, z));
    while (r - l > 1) {
        i32 m = (l + r) / 2;
        if (pred(m, k, z)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (l == 1) {
        i32 cnt = 1;
        for (i32 i = 1; i < n; i++) {
            cnt += s[i] == s[0];
        }
        cout << (cnt >= k) << "\n";
        return;
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

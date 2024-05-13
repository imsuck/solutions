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
// #define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i64 n, k, pb, ps;
    cin >> n >> k >> pb >> ps;
    vec<i32> p(n + 1), a(n + 1);
    for (i32 i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vec<i64> sb, ss;
    i64 cur = 0;
    for (i32 i = 0; i < min(n, k); i++) {
        sb.push_back(cur + (k-i) * a[pb]);
        cur += a[pb];
        pb = p[pb];
    }
    cur = 0;
    for (i32 i = 0; i < min(n, k); i++) {
        ss.push_back(cur + (k-i) * a[ps]);
        cur += a[ps];
        ps = p[ps];
    }
    i64 best_b = *max_element(all(sb)), best_s = *max_element(all(ss));
    if (best_b == best_s) {
        cout << "Draw\n";
    } else if (best_b > best_s) {
        cout << "Bodya\n";
    } else {
        cout << "Sasha\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

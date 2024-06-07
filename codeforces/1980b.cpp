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
    i32 n, f, k;
    cin >> n >> f >> k;
    f--;
    vec<i32> v(n);
    for (i32 &i : v) {
        cin >> i;
    }
    if (k == 0) {
        cout << "NO\n";
        return;
    }
    if (k == n) {
        cout << "YES\n";
        return;
    }
    i32 val = v[f];
    sort(rbegin(v), rend(v));
    cout << (val > v[k] ? "YES" : (val == v[k] && v[k-1] == v[k]) ? "MAYBE" : "NO") << "\n";
    // dbg(v, v[k], val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

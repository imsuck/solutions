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

const i32 MOD = 1e9 + 7;

i64 mod_inv(i64 a) {
    i64 b = MOD, x = 1, y = 0;
    while (a != 1) {
        y -= b / a * x;
        b %= a;
        swap(a, b);
        swap(x, y);
    }
    return x < 0 ? x + MOD : x;
}

void solve() {
    i32 n;
    cin >> n;
    if (n & 1) {
        cout << "0\n";
        return;
    }
    n /= 2;
    vec<i64> p(2*n + 1);
    p[1] = 1;
    for (i32 i = 2; i <= 2*n; i++)
        p[i] = i * p[i-1] % MOD;
    i64 ans = mod_inv(n+1) * p[2*n] % MOD;
    ans = ans * mod_inv(p[n] * p[n] % MOD) % MOD;
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

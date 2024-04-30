#include <bits/stdc++.h>
using namespace std;

/*********** template stuff ***********/
#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
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

istream &operator>>(istream &, i128 &);
ostream &operator<<(ostream &, i128);
istream &operator>>(istream &, u128 &);
ostream &operator<<(ostream &, u128);
/*********** template stuff ***********/

void solve() {
    i64 n;
    cin >> n;
    vec<i64> v(n + 1), p(n + 1, 0);
    for (i32 i = 1; i <= n; i++) {
        cin >> v[i];
        p[i] = p[i - 1] + v[i];
    }

    i64 mx = 0;

    for (i32 k = 1; k < n; k++) {
        if (n % k == 0) {
            vec<i64> sums;
            for (i32 i = k; i <= n; i += k) {
                sums.pb(p[i] - p[i - k]);
            }
            sort(all(sums));
            i64 mn = sums[0];
            for (i32 i = 1; i < sums.len(); i++) {
                mx = max(mx, sums[i] - mn);
                mn = min(mn, sums[i]);
            }
        }
    }

    cout << mx << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

/****** template stuff ******/
istream &operator>>(istream &is, i128 &x) {
    string s;
    x = 0, is >> s;
    bool neg = s[0] == '-';
    for (i32 i = neg; i < i32(s.size()); i++)
        x *= 10, x += s[i] - '0';
    x = neg ? -x : x;
    return is;
}
ostream &operator<<(ostream &os, i128 x) {
    os << (x < 0 ? x = -x, "-" : "");
    if (x > 9)
        os << x / 10;
    return os << i32(x % 10);
}

istream &operator>>(istream &is, u128 &x) {
    string s;
    x = 0, is >> s;
    for (const char &c : s)
        x *= 10, x += c - '0';
    return is;
}
ostream &operator<<(ostream &os, u128 x) {
    if (x > 9)
        os << x / 10;
    return os << i32(x % 10);
}
/****** template stuff ******/

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
    i32 n;
    cin >> n;
    vec<i32> v(n);
    vec<i32> m = {2, 1};
    for (i32 &i : v) {
        cin >> i;
    }
    i64 oc = v[0] & 1, s = v[0];
    cout << v[0] << " \n"[n == 1];
    for (i32 i = 1; i < n; i++) {
        s += v[i];
        oc += v[i] & 1;
        cout << s - oc / 3 - (oc % 3 == 1) << " \n"[i == n - 1];
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

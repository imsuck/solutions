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

vec<pair<i32, i32>> gen_tup(i32 x, i32 y, i32 n) {
    return {{x, y}, {n - y - 1, x}, {n - x - 1, n - y - 1}, {y, n - x - 1}};
}

void solve() {
    i32 cnt = 0;
    i32 n;
    cin >> n;
    vec<vec<char>> sq(n, vec<char>(n));
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < n; j++) {
            cin >> sq[i][j];
        }
    }
    for (i32 i = 0; i < (n + 1) / 2; i++) {
        for (i32 j = 0; j < (n + 1) / 2; j++) {
            auto t = gen_tup(i, j, n);
            char a = sq[t[0].first][t[0].second],
                 b = sq[t[1].first][t[1].second],
                 c = sq[t[2].first][t[2].second],
                 d = sq[t[3].first][t[3].second];
            char mx = max({a, b, c, d});
            cnt += 4 * mx - (a + b + c + d);
        }
    }
    cout << cnt << "\n";
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

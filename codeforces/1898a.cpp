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
    i32 n, k;
    cin >> n >> k;
    str s;
    cin >> s;
    vec<i32> c(26, 0);

    for (char ch : s) {
        c[ch - 'A']++;
    }
    if (c[1] == k) {
        cout << "0\n";
        return;
    }
    cout << "1\n";
    if (c[1] > k) {
        for (i32 i = 0; i < n; i++) {
            if (s[i] == 'B') {
                c[1]--;
            }
            if (c[1] == k) {
                cout << i + 1 << " A\n";
                break;
            }
        }
        return;
    }
    for (i32 i = 0; i < n; i++) {
        if (s[i] == 'A') {
            c[1]++;
        }
        if (c[1] == k) {
            cout << i + 1 << " B\n";
            break;
        }
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

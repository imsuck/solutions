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

struct BIT {
    i32 n;
    vec<i32> bit;
    BIT(i32 n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    BIT(vec<i32> a) : BIT(a.size()) {
        for (i32 i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    i32 sum(i32 i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    void add(i32 i, i32 k) {
        for (; i <= n; i += i & -i)
            bit[i] += k;
    }
};

void solve() {
    i32 n;
    cin >> n;
    set<i32> b;
    vec<pair<i32, i32>> v(n);
    for (i32 i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        b.insert(v[i].second);
    }

    i32 cnt = 0;
    map<i32, i32> m;

    for (i32 i : b) {
        m[i] = ++cnt;
    }

    sort(all(v));

    BIT bit(n + 1);

    i64 res = 0;
    for (i32 i = n - 1; i >= 0; i--) {
        res += bit.sum(m[v[i].second]);
        bit.add(m[v[i].second], 1);
    }
    cout << res << "\n";
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

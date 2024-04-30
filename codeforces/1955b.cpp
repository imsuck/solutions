#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
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
    i32 n, c, d;
    cin >> n >> c >> d;
    vec<i32> a(n*n);
    multiset<i32> s1, s2;
    for (i32 &i : a) {
        cin >> i;
        s1.insert(i);
    }
    sort(all(a));
    vec<vec<i32>> tab(n, vec<i32>(n));
    tab[0][0] = a[0];
    for (i32 i = 0; i < n; i++) {
        if (i) {
            tab[i][0] = tab[i - 1][0] + c;
        }
        for (i32 j = 1; j < n; j++) {
            tab[i][j] = tab[i][j - 1] + d;
        }
    }
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < n; j++) {
            s2.insert(tab[i][j]);
        }
    }
    cout << (s1 == s2 ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

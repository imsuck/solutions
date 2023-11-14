#include <bits/stdc++.h>
using namespace std;

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

const i32 MAX = 1e6 + 5;
i32 p[MAX];

void sieve() {
    fill_n(p, MAX, 0);
    for (i64 i = 2; i < MAX; i++) {
        if (p[i] == 0) {
            for (i64 j = i; j < MAX; j += i) {
                p[j] = i;
            }
        }
    }
}

void solve() {
    i32 n;
    cin >> n;
    vec<i32> v(n);
    map<i32, i32> m;
    for (i32 &x : v) {
        cin >> x;
    }
    for (i32 i : v) {
        while (i != 1) {
            m[p[i]]++;
            i /= p[i];
        }
    }
    bool yes = true;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second % n != 0) {
            yes = false;
            break;
        }
    }
    cout << (yes ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

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
    i32 n;
    cin >> n;
    vec<i32> a(n), b(n);
    for (i32 &i : a) {
        cin >> i;
    }
    for (i32 &i : b) {
        cin >> i;
    }
    i32 m;
    cin >> m;
    vec<i32> d(m);
    for (i32 &i : d) {
        cin >> i;
    }

    i32 aa = 0;
    map<i32,i32> m1, m2;
    for (i32 i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            m1[b[i]]++;
            aa++;
        } else {
            m2[b[i]]++;
        }
    }

    bool ok = false;
    i32 cnt = 0;
    for (i32 i = m - 1; i >= 0; i--) {
        i32 c1 = m1[d[i]], c2 = m2[d[i]];
        if (c1 + c2) {
            ok = true;
            cnt += bool(c1);
            if (c1) {
                m1[d[i]]--;
            }
        }
        if (!ok && c2 == 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << (cnt >= aa ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

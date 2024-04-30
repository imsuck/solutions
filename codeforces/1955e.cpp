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
    i32 n;
    cin >> n;
    str s;
    cin >> s;
    s = '^' + s;
    for (i32 k = n; k >= 2; k--) {
        i32 cnt = 0;
        i32 i = 1;
        vec<i32> p(n + 1, 0);
        for (i = 1; i <= n - k + 1; i++) {
            i32 l = max(i - k + 1, 1);
            i32 e = p[i - 1] - p[l - 1];
            cnt += (s[i] - '0' + e) % 2 == 0;
            p[i] = cnt;
        }
        bool ok = true;
        while (i <= n) {
            i32 cur = s[i] - '0';
            i32 l = max(i - k, 0);
            i32 e = p[i - 1] - p[l];
            ok &= (cur + e) % 2 != 0;
            p[i] = p[i - 1];
            i++;
        }
        if (ok) {
            cout << k << "\n";
            return;
        }
    }
    cout << "1\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}

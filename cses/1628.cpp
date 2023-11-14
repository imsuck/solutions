#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
#define all(a) (a).begin(), (a).end()

void solve() {
    i32 n, x;
    cin >> n >> x;
    vector<i32> a(n / 2), b((n + 1) / 2), v1, v2;
    for (i32 i = 0; i < n; i++) {
        if (i < n / 2) {
            cin >> a[i];
        } else {
            cin >> b[i - n / 2];
        }
    }
    for (i32 l = 0; l < (1 << a.size()); l++) {
        i32 s = 0;
        for (i32 i = 0; i < a.size() && s <= x; i++) {
            if (l >> i & 1) {
                s += a[i];
            }
        }
        if (s <= x) {
            v1.push_back(s);
        }
    }
    for (i32 l = 0; l < (1 << b.size()); l++) {
        i32 s = 0;
        for (i32 i = 0; i < b.size() && s <= x; i++) {
            if (l >> i & 1) {
                s += b[i];
            }
        }
        if (s <= x) {
            v2.push_back(s);
        }
    }
    sort(all(v1));
    sort(all(v2));
    i64 res = 0;
    for (i32 i : v1) {
        auto l = lower_bound(all(v2), x - i), h = upper_bound(all(v2), x - i);
        res += h - l;
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

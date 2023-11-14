#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
#define vec vector

i64 s(i64 l, i64 k) {
    i64 n = k - l + 1;
    return n * (n + 1) / 2;
}

void solve() {
    i64 n, k, q, res = 0;
    cin >> n >> k >> q;
    i64 a[n];
    for (i64 i = 0; i < n; i++)
        cin >> a[i];
    i64 len = 0;
    for (i64 i = 0; i < n; i++) {
        if (a[i] <= q) {
            len++;
        } else {
            if (len >= k)
                res += s(k, len);
            len = 0;
        }
    }
    if (len >= k)
        res += s(k, len);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

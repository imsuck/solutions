#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i64 n;
    cin >> n;
    i64 mid = n * n / 2;

    auto pred = [&](i64 x) {
        int64_t cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += min(x / i, n);
            if (cnt > mid) return false;
        }
        return true;
    };

    i64 l = 0, r = n * n + 1, m;
    while (r - l > 1) {
        m = l + (r - l) / 2;
        if (pred(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << r << "\n";
}

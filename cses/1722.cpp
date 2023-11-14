#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i64 = int64_t;

const i64 MOD = 1e9 + 7;
map<i64, i64> m;

i64 f(i64 n) {
    if (m.count(n)) {
        return m[n];
    }
    i64 k = n / 2;
    if (n % 2 == 0) {
        return m[n] = (f(k) * f(k) + f(k - 1) * f(k - 1)) % MOD;
    } else {
        return m[n] = f(k) * (f(k + 1) + f(k - 1)) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i64 n;
    cin >> n;
    m[-1] = 0;
    m[0] = m[1] = 1;
    cout << f(n - 1) << "\n";
}

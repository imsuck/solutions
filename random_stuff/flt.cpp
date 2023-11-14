#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using i128 = __int128_t;
const i64 MOD = 1e9 + 7;

mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());

i64 power(i64 a, i64 n, i64 p) {
    i64 res = 1;
    a %= p;
    while (n > 0) {
        res = (n & 1) ? i128(res) * a % p : res;
        n >>= 1;
        a = i128(a) * a % p;
    }
    return res;
}

bool flt(i64 n, int k) {
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;
    while (k--) {
        i64 a = 2 + rng() % (n - 4);
        if (__gcd(a, n) != 1 || power(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

int main() {
    i64 n;
    cin >> n;
    cout << n << " is " << (flt(n, 10) ? "a prime" : "not a prime") << "\n";
}

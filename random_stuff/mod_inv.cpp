#include <bits/stdc++.h>
using namespace std;

typedef int64_t i64;

const i64 MOD = 1e9 + 7;

i64 ext_euclid(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 x1, y1, gcd = ext_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}
i64 mod_inv(i64 a) {
    i64 x, y, gcd = ext_euclid(a, MOD, x, y);
    return (gcd == 1) ? (x % MOD + MOD) % MOD : -1;
}
i64 mod_inv_iter(i64 a) {
    i64 b = MOD, x = 1, y = 0;
    while (a != 1) {
        y -= b / a * x;
        b %= a;
        swap(a, b);
        swap(x, y);
    }
    return x < 0 ? x + MOD : x;
}
i64 mod_add(i64 a, i64 b) { return (a % MOD + b % MOD) % MOD; }
i64 mod_sub(i64 a, i64 b) { return (a % MOD - b % MOD + MOD) % MOD; }
i64 mod_mul(i64 a, i64 b) { return ((a % MOD) * (b % MOD)) % MOD; }
i64 mod_div(i64 a, i64 b) {
    i64 b_inv = mod_inv(b);
    return (b_inv != -1) ? mod_mul(a, b_inv) : -1;
}

int main() {
    i64 a, b, x, y;
    i64 mi = mod_inv(a);
    cout << ((mi != -1) ? to_string(mi) : "No") << "\n";
    cout << mod_div(a, b) << "\n";

    return 0;
}

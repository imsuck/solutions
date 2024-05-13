#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
template <typename T> using vec = vector<T>;

const u64 SEED = 42;

u64 gcd(u64 a, u64 b) {
    while (b)
        a %= b, swap(a, b);
    return a;
}

u64 f(u64 x, u64 m) { return (u64)((u128)x * x + 1) % m; }
u64 diff(u64 x, u64 y) { return x > y ? x - y : y - x; }

u64 find_factor(u64 n) {
    u64 x = SEED, y = SEED, g = 1;
    while (g == 1) {
        x = f(f(x, n), n);
        y = f(y, n);
        g = gcd(diff(x, y), n);
    }
    return g;
}

vec<u64> factors(u64 n) {
    vec<u64> res;
    do {
        u64 d = find_factor(n);
        res.emplace_back(d);
        n /= d;
    } while (n > 1);
    return res;
}

int main() {
    u64 n;
    cin >> n;
    vec<u64> fac = factors(n);
    // sort(fac.begin(), fac.end());
    dbg(fac);
}

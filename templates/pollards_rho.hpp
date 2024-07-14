// TODO: Fix this unfinished mess
#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
template<typename T> using vec = vector<T>;

const u32 M = 1024;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> T rd(T l, T r) {
    return uniform_int_distribution<u64>(l, r)(rng);
}

u64 diff(u64 x, u64 y) { return x > y ? x - y : y - x; }

u64 gcd(u64 a, u64 b) {
    if (a == 0) return b;
    if (b == 0) return a;

    u32 az = __builtin_ctzll(a);
    u32 bz = __builtin_ctzll(b);
    u32 shift = min(az, bz);
    b >>= bz;

    while (a) {
        a >>= az;
        u64 df = diff(a, b);
        az = __builtin_ctzll(df);
        b = min(a, b);
        a = df;
    }
    return b << shift;
}

u64 f(u64 x, u64 c, u64 m) { return u64(((u128)x * x + c) % m); }

u64 power(u64 a, u64 n, u64 m) {
    a %= m;
    u64 res = 1;
    while (n) {
        if (n & 1) res = (u128)res * a % m;
        a = (u128)a * a % m;
        n >>= 1;
    }
    return res;
}

constexpr bool miller_rabin(u64 n) {
    if (n <= 1) return false;
    for (u32 prime : {2, 3, 5, 7, 11}) {
        if (n == prime) return true;
        if (n % prime == 0) return false;
    }
    if (n < 121) return true;

    const u32 s = __builtin_ctzll(n - 1);
    const u64 d = (n - 1) >> s;
    for (u64 base : {2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U}) {
        u64 a = base % n;
        if (a == 0) continue;
        u64 x = power(a, d, n);
        if (x == 1) continue;
        for (u32 r = 0;; r++, x = (u128)x * x % n) {
            if (x == n - 1) break;
            if (r == s - 1) return false;
        }
    }
    return true;
}

u64 find_factor(u64 n, u64 seed, u64 c) {
    u64 x = seed;

    for (u32 l = M; l < (1 << 20); l *= 2) {
        u64 y = x, p = 1;
        for (u32 i = 0; i < l; i += M) {
            for (u32 j = 0; j < M; j++) {
                y = f(y, c, n);
                p = (u128)p * diff(x, y) % n;
            }
            u64 g = gcd(p, n);
            if (g != 1) return g;
        }
    }
    return 1;
}

vec<u64> factors(u64 n) {
    vec<u64> res;
    if (n == 1) return res;
    do {
        u64 d = 1;
        while (!miller_rabin(d)) {
            d = find_factor(n, rd((u64)1, n - 1), rd((u64)1, n - 1));
        }
        while (n % d == 0) {
            res.emplace_back(d);
            n /= d;
        }
    } while (n > 1);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    u32 tt;
    cin >> tt;
    while (tt--) {
        u64 n;
        cin >> n;
        vec<u64> fac = factors(n);
        sort(fac.begin(), fac.end());
        cout << fac.size() << " ";
        for (u64 i : fac) {
            cout << i << " ";
        }
        cout << "\n";
    }
}

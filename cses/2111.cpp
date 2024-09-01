// Just use FFT instead
#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

#pragma GCC diagnostic ignored "-Wconversion"

u64 power(u64 a, u64 n, u64 m) {
    u64 r = 1;
    while (n) {
        if (n & 1) r = r * a % m;
        a = a * a % m, n >>= 1;
    }
    return r;
}

u64 inv_mod(i64 a, u64 m) {
    i64 b = m, x = 1, y = 0;
    while (b) {
        x = exchange(y, x - a / b * y);
        a = exchange(b, a % b);
    }
    assert(a == 1);
    return x < 0 ? x + m : x;
}

constexpr u32 get_pr(u32 m) {
    if (m == 998244353) return 3;
    else if (m == 985661441) return 3;
}

template<u32 mod> void ntt(vector<u32> &a) {
    constexpr u32 pr = get_pr(mod);

    u32 n = a.size();
    for (u32 m = n; m > 1; m >>= 1) {
        u32 omega = power(pr, (mod - 1) / m, mod);
        for (u32 s = 0; s < n; s += m) {
            u32 w = 1;
            for (u32 i = 0; i < m / 2; i++) {
                u32 l = a[s | i];
                u32 r = a[s | i | m >> 1];
                a[s | i] = (l + r) % mod;
                a[s | i | m >> 1] = u64(l + mod - r) % mod * w % mod;
                w = (u64)w * omega % mod;
            }
        }
    }
}
template<u32 mod> void intt(vector<u32> &a) {
    constexpr u32 pr = get_pr(mod);

    u32 n = a.size();
    for (u32 m = 2; m <= n; m <<= 1) {
        u32 omega = inv_mod(power(pr, (mod - 1) / m, mod), mod);
        for (u32 s = 0; s < n; s += m) {
            u32 w = 1;
            for (u32 i = 0; i < m / 2; i++) {
                u32 l = a[s | i];
                u32 r = (u64)a[s | i | m >> 1] * w % mod;
                a[s | i] = (l + r) % mod;
                a[s | i | m >> 1] = (l + mod - r) % mod;
                w = (u64)w * omega % mod;
            }
        }
    }
    u32 n_inv = inv_mod(n, mod);
    for (u32 &i : a) i = (u64)i * n_inv % mod;
}
template<u32 mod> vector<u32> convolve(vector<u32> a, vector<u32> b) {
    u32 n = a.size() + b.size() - 1;
    u32 m = 1;
    while (m < n) m <<= 1;
    a.resize(m), b.resize(m);
    ntt<mod>(a), ntt<mod>(b);
    for (u32 i = 0; i < m; i++) a[i] = (u64)a[i] * b[i] % mod;
    intt<mod>(a);
    a.resize(n);
    return a;
}

inline void mod_vec(vector<u32> &a, u32 m) { for (u32 &i : a) i %= m; }

i64 garner(const vector<i64> &r, const vector<i64> &m, i64 mod = numeric_limits<i64>::max()) {
    u32 n = r.size();
    vector<i64> a(n);
    auto pref = [&](u32 i, u64 md) {
        i64 res = 0, prd = 1;
        for (u32 j = 0; j < i; j++) {
            (res += a[j] * prd) %= md,
            (prd *= m[j]) %= md;
        }
        return res;
    };
    for (u32 i = 0; i < n; i++) {
        a[i] = (r[i] - pref(i, m[i])) % m[i];
        if (a[i] < 0) a[i] += m[i];
        for (u32 j = 0; j < i; j++) (a[i] *= inv_mod(m[j], m[i])) %= m[i];
    }
    return pref(n, mod);
}

vector<u64> convolve(const vector<u32> &a, const vector<u32> &b) {
    const u32 MOD1 = 998244353;
    const u32 MOD2 = 985661441;
    vector<u32> a1 = a, b1 = b, a2 = a, b2 = b;
    mod_vec(a1, MOD1), mod_vec(b1, MOD1);
    mod_vec(a2, MOD2), mod_vec(b2, MOD2);
    auto c1 = convolve<MOD1>(a1, b1);
    auto c2 = convolve<MOD2>(a2, b2);
    vector<u64> c(c1.size());
    const vector<i64> mods = {998244353, 985661441};
    for (u32 i = 0; i < c.size(); i++) c[i] = garner({c1[i], c2[i]}, mods);
    return c;
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    u32 k, n, m;
    cin >> k >> n >> m;

    vector<u32> a(k + 1), b(k + 1);
    for (u32 i = 0, x; i < n; i++) cin >> x, a[x]++;
    for (u32 i = 0, x; i < m; i++) cin >> x, b[x]++;

    auto c = convolve(a, b);
    for (u32 i = 2; i <= 2 * k; i++) cout << c[i] << " \n"[i == 2 * k];
}

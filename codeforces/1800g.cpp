#include <bits/stdc++.h>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class T> y_comb_t(T &&_f) : f(forward<T>(_f)) {}
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(/* ref */ (*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;
template<class T> fn len(const T &x) -> i32 { return i32(x.size()); }

seed_seq sseq{
    (u64)chrono::steady_clock::now().time_since_epoch().count(),
    (u64)__builtin_ia32_rdtsc(),
    (u64)make_unique<char>().get()
};
mt19937_64 mt(sseq);
template<class I> fn rng(I l, I r) -> I {
    return uniform_int_distribution<I>{l, r}(mt);
}

const u64 mod = (1ULL << 61) - 1;
fn add(u64 a, u64 b) -> u64 { return (a += b) < mod ? a : a + mod; }
fn red(u64 a) -> u64 { return add(a & mod, a >> 61); }
fn mul(u64 a, u64 b) -> u64 {
    u64 la = u32(a), ha = a >> 32, lb = u32(b), hb = b >> 32;
    u64 l = la * lb, m = la * hb + ha * lb, h = ha * hb;
    return red((l & mod) + (l >> 61) + (m >> 29) + (m << 32 & mod) + (h << 3));
}
fn weyl(u64 a) -> u64 {
    static const u64 x = rng<u64>(0, mod - 1), y = rng<u64>(0, mod - 1);
    return add(mul(a, x), y);
}

fn solve() {
    i32 n;
    cin >> n;
    vec<basic_string<i32>> g(n);
    for (i32 i = 1, u, v; i < n; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v, g[v] += u;
    }

    vec<char> sym(n);
    vec<i32> par(n, -1), h(n);
    y_comb([&](auto &self, i32 v) -> i32 {
        for (i32 c : g[v])
            if (c != par[v]) par[c] = v, h[v] = max(h[v], self(c) + 1);
        return h[v];
    })(0);
    vec<u64> val(n, 1);
    y_comb([&](auto &self, i32 v) -> u64 {
        map<u64, i32> m, inv;
        for (i32 c : g[v]) {
            if (c == par[v]) continue;
            val[v] = mul(val[v], add(weyl(h[v]), self(c)));
            m[val[c]]++;
            inv[val[c]] = c;
        }
        i32 o = 0, id;
        for (auto [a, b] : m) b & 1 ? o++, id = inv[a] : 0;
        if (o == 0) {
            sym[v] = true;
        } else if (o == 1) {
            sym[v] = sym[id];
        } else {
            sym[v] = false;
        }
        return val[v];
    })(0);
    cout << (sym[0] ? "YES" : "NO") << "\n";
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}

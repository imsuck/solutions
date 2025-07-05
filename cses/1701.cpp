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

const i32 mod = i32(1e9) + 7;
fn add(i32 a, i32 b) -> i32 { return (a += b) < mod ? a : a - mod; }
fn mul(u64 a, i32 b) -> i32 { return i32(a * b % mod); }
fn weyl(i32 a) -> i32 {
    static const u64 x = rng<u32>(0, mod - 1), y = rng<u32>(0, mod - 1);
    return i32((a * x + y) % mod);
}

template<class G> fn centroid(const G &g) -> vec<i32> {
    const i32 n = len(g);
    vec<i32> sz(n, 1), par(n, -1), ret;
    y_comb([&](auto &self, i32 v) -> i32 {
        for (i32 c : g[v])
            if (c != par[v]) par[c] = v, sz[v] += self(c);
        return sz[v];
    })(0);
    i32 size = n;
    for (i32 i = 0; i < n; i++) {
        i32 val = n - sz[i];
        for (i32 c : g[i])
            if (c != par[i]) val = max(val, sz[c]);
        if (val < size) size = val, ret.clear();
        if (val == size) ret.push_back(i);
    }
    return ret;
}
template<class G> fn tree_hash(const G &g, i32 root = 0) -> i32 {
    const i32 n = len(g);
    vec<i32> h(n);
    y_comb([&](auto &self, i32 v, i32 p) -> i32 {
        for (i32 c : g[v])
            if (c != p) h[v] = max(h[v], self(c, v) + 1);
        return h[v];
    })(root, -1);
    return y_comb([&](auto &self, i32 v, i32 p) -> i32 {
        i32 val = 1;
        for (i32 c : g[v]) {
            if (c == p) continue;
            val = mul(val, add(weyl(h[v]), self(c, v)));
        }
        return val;
    })(root, -1);
}

fn solve() {
    i32 n;
    cin >> n;
    vec<basic_string<i32>> a(n), b(n);
    for (i32 i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v, u--, v--;
        a[u] += v, a[v] += u;
    }
    for (i32 i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v, u--, v--;
        b[u] += v, b[v] += u;
    }

    auto ca = centroid(a), cb = centroid(b);
    for (i32 ra : ca) {
        for (i32 rb : cb) {
            if (tree_hash(a, ra) == tree_hash(b, rb)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}

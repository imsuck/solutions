#include <bits/stdc++.h>
using namespace std;

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

const i32 mod = (i32)1e9 + 7;
fn add(i32 a, i32 b) -> i32 { return (a += b) < mod ? a : a - mod; }
fn sub(i32 a, i32 b) -> i32 { return add(a, mod - b); }
fn mul(i64 a, i32 b) -> i32 { return i32(a * b % mod); }
fn inv(i32 a) {
    i32 b = mod, x = 1, y = 0;
    while (b) {
        x = exchange(y, x - a / b * y);
        a = exchange(b, a % b);
    }
    return x < 0 ? x + mod : x;
}

const i32 N = (i32)2e6 + 5;
i32 fac[N], ifac[N];

fn proc() {
    fac[0] = 1;
    for (i32 i = 1; i < N; i++) fac[i] = mul(i, fac[i - 1]);
    ifac[N - 1] = inv(fac[N - 1]);
    for (i32 i = N - 2; i >= 0; i--) ifac[i] = mul(i + 1, ifac[i + 1]);
}

fn comb(i32 n, i32 k) -> i32 { return mul(fac[n], mul(ifac[k], ifac[n - k])); }
fn paths(i32 a, i32 b) -> i32 { return comb(a + b, a); }

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<array<i32, 2>> traps(m);
    vec<i32> dp(m + 1);
    for (auto &[y, x] : traps) cin >> y >> x;
    sort(begin(traps), end(traps));
    traps.push_back({n, n});
    for (i32 i = 0; i <= m; i++) {
        auto [yi, xi] = traps[i];
        dp[i] = paths(xi - 1, yi - 1);
        for (i32 j = 0; j < i; j++) {
            if (traps[i][0] < traps[j][0] || traps[i][1] < traps[j][1])
                continue;
            auto [yj, xj] = traps[j];
            dp[i] = sub(dp[i], mul(dp[j], paths(xi - xj, yi - yj)));
        }
    }
    cout << dp.back() << "\n";
}

fn main() -> i32 {
    proc();
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}

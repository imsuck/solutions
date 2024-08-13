#include <bits/stdc++.h>
using namespace std;

// clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M, class S = typename M::S> struct SegTree {
    SegTree() = default;
    SegTree(int _n) : n(_n), t(n * 2, M::e) {}
    SegTree(const vector<S> &v) : SegTree(v.size()) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n - 1; i > 0; i--) update(i);
    }
    void set(int p, S val) {
        assert(0 <= p && p < n);
        for (t[p += n] = val; p >>= 1;) update(p);
    }
    S get(int p) const {
        assert(0 <= p && p < n);
        return t[p + n];
    }
    S all_prod() const { return prod(0, n); }
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        S resl = M::e, resr = M::e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }

  private:
    int n;
    vector<S> t;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};
#pragma GCC diagnostic pop
// clang-format on

#ifndef LOCAL
    #define dbg(...) 42
#endif

using u32 = uint32_t;
using u64 = uint64_t;
using str = string;
#define vec vector

struct Info {
    u64 hash = 0, rhash = 0;
    u32 sz = 0;
    static Info from(char c) { return Info{u64(c), u64(c), 1}; }
    bool is_palindrome() { return hash == rhash; }
};

mt19937_64 mt(u64(make_unique<char>().get()));
const u64 BASE = uniform_int_distribution<u64>{256, (1ull << 61) - 2}(mt);

#pragma GCC diagnostic ignored "-Wc++17-extensions"
struct HashOnSegTree {
    using S = Info;
    static inline constexpr S e{};
    static S op(const S &l, const S &r) {
        ensure_pows(max(l.sz, r.sz));
        return S{
            add(mul(l.hash, pows[r.sz]), r.hash),
            add(l.rhash, mul(r.rhash, pows[l.sz])),
            l.sz + r.sz,
        };
    }

  private:
    static constexpr u64 mod = (u64(1) << 61) - 1;

    static inline const u64 base = BASE;
    static inline vector<u64> pows{1};
    static void ensure_pows(u32 n) {
        while (pows.size() <= n) pows.push_back(mul(pows.back(), base));
    }

    static u64 fast_mod(u64 x) { return add(x >> 61, x & mod); }
    static u64 add(u64 a, u64 b) { return a += b, a < mod ? a : a - mod; }
    static u64 mul(u64 a, u64 b) {
        auto r = (__uint128_t)a * b;
        return add(u64(r >> 61), r & mod);
    }
};

void solve() {
    int n, q;
    str s;
    cin >> n >> q;
    cin >> s;

    vector<Info> init(n);
    for (int i = 0; i < n; i++) init[i] = Info::from(s[i]);

    SegTree<HashOnSegTree> st(init);
    while (q--) {
        int qt, a, b;
        char c;
        cin >> qt >> a;
        a--;
        if (qt == 1) {
            cin >> c;
            st.set(a, Info::from(c));
        } else {
            cin >> b;
            cout << (st.prod(a, b).is_palindrome() ? "YES" : "NO") << "\n";
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

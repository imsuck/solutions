#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

// clang-format off
template<class T = int> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    template<class... Ts> void push(Ts &...x) { (_push(x), ...); }
    void build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1;
        for (auto x : val) {
            if (og.empty() || og.back() != x) id++, og.push_back(x);
            x.get() = id;
        }
    }
    int size() const { return int(og.size()); }
    T operator[](int i) const { return og[i]; }
    int operator()(T x) const { return int(lower_bound(begin(og), end(og), x) - begin(og)); }
    bool find(T x) const { return binary_search(begin(og), end(og), x); }

  private:
    void _push(T &x) { val.push_back(x); }
    void _push(pair<T, T> &p) { push(p.first, p.second); }
    template<class V> void _push(V &a) { for (auto &x : a) _push(x); }
};
// clang-format on

template<class M> struct SegTree {
    using T = typename M::T;

    int n, m;
    vector<T> t;

    SegTree() = default;
    SegTree(int _n) : n(_n), m(bit_ceil(n)), t(2 * m, M::id()) {}
    template<class V> SegTree(const V &v) : SegTree(int(v.size())) {
        copy(begin(v), end(v), begin(t) + m);
        for (int i = m; --i;) update(i);
    }
    void set(int p, T val) {
        for (t[p += m] = val; p >>= 1;) update(p);
    }
    T operator[](int p) const { return t[p + m]; }
    T operator()(int l, int r) const {
        T resl = M::id(), resr = M::id();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }

  private:
    // clang-format off
    static int bit_ceil(int n) { int m = 1; while (m < n) m *= 2; return m; }
    // clang-format on
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
template<class T> using vec = vector<T>;

struct Min {
    using T = i32;
    static T id() { return i32(1.1e9); }
    static T op(T l, T r) { return min(l, r); }
};

fn solve() {
    Compressor val;

    i32 n, q;
    cin >> n >> q;
    vec<i32> a(n);
    for (i32 &i : a) cin >> i, val.push(i);
    vec<array<i32, 3>> qs(q);
    for (auto &[t, x, y] : qs) {
        cin >> t >> x >> y, x--;
        if (t == 1) val.push(y);
    }
    val.build();

    vec<map<int, int>> nxt(val.size(), {pair(n, n)});
    SegTree<Min> st = ({
        vec<i32> init(n);
        for (i32 i = n - 1; i >= 0; i--)
            init[i] = nxt[a[i]][i] = begin(nxt[a[i]])->first;
        init;
    });

    for (auto &[t, x, y] : qs) {
        if (t == 1) {
            auto it = nxt[a[x]].lower_bound(x);
            if (it != nxt[a[x]].begin()) {
                auto &[pi, pn] = *prev(it);
                st.set(pi, pn = it->second);
            }
            nxt[a[x]].erase(it);

            it = nxt[y].lower_bound(x);
            if (it != nxt[y].begin()) {
                auto &[pi, pn] = *prev(it);
                pn = x;
                st.set(pi, pn);
            }
            nxt[y].emplace(x, it->first);
            st.set(x, nxt[y][x]);

            a[x] = y;
        } else {
            cout << (st(x, y) >= y ? "YES" : "NO") << "\n";
        }
    }
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}

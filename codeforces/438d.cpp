#include <bits/stdc++.h>
using namespace std;

template<class M> struct LazySegTree {
    using T = typename M::T;
    using F = typename M::F;

    int n, lg = 0;
    vector<T> t;
    vector<F> lz;

    LazySegTree(int _n) : n(_n), t(2 * n, M::id()), lz(n, M::fid()) {
        while (1 << lg < n) lg++;
    }
    LazySegTree(const vector<T> &v) : LazySegTree(int(v.size())) {
        copy_n(begin(v), n, begin(t) + n);
        for (int i = n; --i;) update(i);
    }

    void set(int p, const T &x) { t[p + n] = x, update_from(p); }
    T operator()(int l, int r) {
        T sml = M::id(), smr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }
    void apply(int l, int r, const F &f) {
        for (int l2 = l + n, r2 = r + n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        int li = __builtin_ctz(l + n), ri = __builtin_ctz(r + n);
        update_from(l, li), update_from(r - 1, ri);
    }

    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
    void update_from(int p, int l = 0) {
        p += n;
        for (int i = l + 1; i <= lg; i++) update(p >> i);
    }
    void all_apply(int p, const F &f) {
        bool ok = M::map(f, t[p]);
        assert(p < n || ok);
        if (p < n) {
            lz[p] = f;
            if (!ok) push(p), update(p);
        }
    }
    void push(int p) {
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = M::fid();
    }
};

using i64 = int64_t;

struct M {
    struct T {
        i64 sum = 0;
        int mx = 0, sz = 0;
        static T from_int(int x) { return {x, x, 1}; }
    };
    using F = int;

    static T id() { return {}; }
    static F fid() { return 0; }

    static T op(const T &l, const T &r) {
        return {l.sum + r.sum, max(l.mx, r.mx)};
    }
    static bool map(F f, T &x) {
        if (f == 0) return true;
        if (x.sz == 1) {
            x.sum = x.mx = x.sum % f;
            return true;
        }
        return x.mx < f;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    using T = M::T;

    vector<M::T> a(n);
    for (auto &e : a) {
        int x;
        cin >> x;
        e = T::from_int(x);
    }

    LazySegTree<M> st(a);
    while (q--) {
        int t, l, r, x;
        cin >> t;
        if (t == 1) {
            cin >> l >> r, l--;
            cout << st(l, r).sum << "\n";
        } else if (t == 2) {
            cin >> l >> r >> x, l--;
            st.apply(l, r, x);
        } else {
            int k;
            cin >> k >> x, k--;
            st.set(k, T::from_int(x));
        }
    }
}

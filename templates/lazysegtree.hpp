#include <cassert>
#include <vector>
using namespace std;

// M: S M::e, F M::id, S op(S, S), F comp(F, F), bool map(F, &S)
// clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M, class S = typename M::S, class F = typename M::F>
struct LazySegTree {
    LazySegTree() = default;
    LazySegTree(int _n) : n(_n) {
        while (1 << lg < n) lg++;
        m = 1 << lg, t.assign(m * 2, M::e), upd.resize(m), lz.assign(m, M::id);
    }
    LazySegTree(const vector<S> &v) : LazySegTree(v.size()) {
        copy(begin(v), end(v), begin(t) + m);
        for (int i = m - 1; i > 0; i--) update(i);
    }

    void set(int p, const S &x) {
        assert(0 <= p && p < n);
        push_to(p), t[p + m] = x, update_from(p);
    }
    S operator[](int p) {
        assert(0 <= p && p < n);
        return push_to(p), t[p + m];
    }
    S get(int p) { return (*this)[p]; }

    S operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::e;
        push_to(l), push_to(r);
        S sml = M::e, smr = M::e;
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }
    S prod(int l, int r) { return (*this)(l, r); }
    S all_prod() const { return t[1]; }

    void apply(int p, const F &f) {
        assert(0 <= p && p < n);
        push_to(p), M::map(f, t[p + m]), update_from(p);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        push_to(l), push_to(r);
        for (int l2 = l += m, r2 = r += m; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; i++) update(l >> i);
        for (int i = ri + 1; i <= lg; i++) update(r >> i);
    }

  private:
    int n, m, lg = 0;
    vector<S> t;
    vector<bool> upd;
    vector<F> lz;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
    void update_from(int p) {
        p += m;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    void all_apply(int p, const F &f) {
        bool ok = M::map(f, t[p]);
        assert(p < m || ok);
        if (p < m) {
            lz[p] = M::comp(f, lz[p]), upd[p] = true;
            if (!ok) push(p), update(p);
        }
    }
    void push(int p) {
        if (!upd[p]) return;
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = M::id, upd[p] = false;
    }
    void push_to(int p) {
        p += m;
        for (int i = lg; i >= 1; i--) push(p >> i);
    }
};
#pragma GCC diagnostic pop
// clang-format on

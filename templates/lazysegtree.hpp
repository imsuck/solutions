#include <cassert>
#include <vector>
using namespace std;

// M: T M::id(), F M::fid(), T op(T, T), F comp(F, F), bool map(F, &T)
// clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M> struct LazySegTree {
    using T = typename M::T;
    using F = typename M::F;
    LazySegTree() = default;
    LazySegTree(int _n) : n(_n), t(n * 2, M::id()), upd(n), lz(n, M::fid()) {
        while (1 << lg < n) lg++;
    }
    LazySegTree(const vector<T> &v) : LazySegTree(v.size()) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n; --i;) update(i);
    }

    void set(int p, const T &x) {
        assert(0 <= p && p < n);
        push_to(p), t[p + n] = x, update_from(p);
    }
    T operator[](int p) {
        assert(0 <= p && p < n);
        return push_to(p), t[p + n];
    }
    T get(int p) { return (*this)[p]; }

    T operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::id();
        push_to(l), push_to(r - 1);
        T sml = M::id(), smr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }
    T prod(int l, int r) { return (*this)(l, r); }
    T all_prod() { return (*this)(0, n); }

    void apply(int p, const F &f) {
        assert(0 <= p && p < n);
        push_to(p), M::map(f, t[p + n]), update_from(p);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        push_to(l), push_to(r - 1);
        for (int l2 = l += n, r2 = r += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; i++) update(l >> i);
        for (int i = ri + 1; i <= lg; i++) update((r - 1) >> i);
    }

  private:
    int n, lg = 0;
    vector<T> t;
    vector<bool> upd;
    vector<F> lz;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
    void update_from(int p) {
        p += n;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    void all_apply(int p, const F &f) {
        bool ok = M::map(f, t[p]);
        assert(p < n || ok);
        if (p < n) {
            lz[p] = M::comp(f, lz[p]), upd[p] = true;
            if (!ok) push(p), update(p);
        }
    }
    void push(int p) {
        if (!upd[p]) return;
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = M::fid(), upd[p] = false;
    }
    void push_to(int p) {
        p += n;
        for (int i = lg; i >= 1; i--) push(p >> i);
    }
};
#pragma GCC diagnostic pop
// clang-format on

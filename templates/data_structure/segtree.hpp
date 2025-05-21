#include <cassert>
#include <vector>
using namespace std;

// Modified version of atcoder library's segtree.hpp
template<class M> struct SegTree {
    using T = typename M::T;

    const int n, m;
    vector<T> t;

    SegTree() = default;
    SegTree(int _n) : n(_n), m(bit_ceil(n)), t(2 * m, M::id()) {}
    template<class V> SegTree(const V &v) : SegTree(int(v.size())) {
        copy(begin(v), end(v), begin(t) + m);
        for (int i = m; --i;) update(i);
    }
    void set(int p, T val) {
        assert(0 <= p && p < n);
        for (t[p += m] = val; p /= 2;) update(p);
    }
    T operator[](int p) const {
        assert(0 <= p && p < n);
        return t[p + m];
    }
    T get(int p) const { return (*this)[p]; }
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = M::id(), resr = M::id();
        for (l += m, r += m; l < r; l /= 2, r /= 2) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }
    T prod(int l, int r) const { return (*this)(l, r); }
    T all_prod() const { return t[1]; }
    template<class G> int max_right(int l, G &&g) const {
        assert(0 <= l && l <= n);
        assert(g(M::id()));
        if (l == n) return n;
        l += m;
        T sm = M::id();
        do {
            for (; l % 2 == 0; l /= 2);
            if (!g(M::op(sm, t[l]))) {
                while (l < m) {
                    l = 2 * l;
                    if (g(M::op(sm, t[l]))) sm = M::op(sm, t[l++]);
                }
                return l - m;
            }
            sm = M::op(sm, t[l++]);
        } while ((l & -l) != l);
        return n;
    }
    template<class G> int min_left(int r, G &&g) const {
        assert(0 <= r && r <= n);
        assert(g(M::id()));
        if (r == 0) return 0;
        r += m;
        T sm = M::id();
        do {
            for (r--; r > 1 && r % 2; r /= 2);
            if (!g(M::op(t[r], sm))) {
                while (r < m) {
                    r = 2 * r + 1;
                    if (g(M::op(t[r], sm))) sm = M::op(t[r--], sm);
                }
                return r + 1 - m;
            }
            sm = M::op(t[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    // clang-format off
    static int bit_ceil(int n) { int m = 1; while (m < n) m *= 2; return m; }
    // clang-format on
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};

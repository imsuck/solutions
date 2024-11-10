#include <cassert>
#include <vector>
using namespace std;

// Modified version of atcoder library's segtree.hpp
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M> struct SegTree {
    using T = typename M::T;
    SegTree() = default;
    SegTree(int _n) : n(_n), t(n * 2, M::id()) {}
    SegTree(const vector<T> &v) : SegTree(v.size()) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n; --i;) update(i);
    }
    void set(int p, T val) {
        assert(0 <= p && p < n);
        for (t[p += n] = val; p >>= 1;) update(p);
    }
    T operator[](int p) const {
        assert(0 <= p && p < n);
        return t[p + n];
    }
    T get(int p) const { return (*this)[p]; }
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = M::id(), resr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }
    T prod(int l, int r) const { return (*this)(l, r); }
    T all_prod() const { return (*this)(0, n); }

  private:
    int n;
    vector<T> t;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};
#pragma GCC diagnostic pop

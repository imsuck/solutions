#include <cassert>
#include <vector>
using namespace std;

// Modified version of atcoder library's segtree.hpp
// clang-format off
#pragma GCC diagnostic ignored "-Wconversion"
template<class S> struct SegTree {
  public:
    SegTree() : SegTree(0) {}
    SegTree(int _n) : n(_n), t(2 * _n, S::e()) {}
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

        S resl = S::e(), resr = S::e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
        }

        return resl + resr;
    }

  private:
    int n;
    vector<S> t;
    void update(int p) { t[p] = t[p << 1] + t[p << 1 | 1]; }
};
#pragma GCC diagnostic warning "-Wconversion"
// clang-format on

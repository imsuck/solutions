#include <bits/stdc++.h>
using namespace std;

template <typename T> struct SegTree {
    using usize = uintmax_t;

  public:
    SegTree() : SegTree(0) {}
    SegTree(usize n) : n(n), t(2 * n) {}
    SegTree(const vector<T> &v) : SegTree(v.size()) {
        for (usize i = 0; i < n; i++)
            t[i + n] = v[i];
        for (usize i = n - 1; i > 0; i--)
            update(i);
    }
    void set(usize p, T val) {
        for (t[p += n] = val; p >>= 1;)
            update(p);
    }
    T query(usize l, usize r) {
        T resl = T::id(), resr = T::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = resl + t[l++];
            if (r & 1)
                resr = t[--r] + resr;
        }

        return resl + resr;
    }

  private:
    usize n;
    vector<T> t;
    void update(usize p) { t[p] = t[p << 1] + t[p << 1 | 1]; }
};

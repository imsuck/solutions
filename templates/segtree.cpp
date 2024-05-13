#include <bits/stdc++.h>
using namespace std;

template <typename T> struct SegTree {
    using usize = uintmax_t;

  private:
    struct Node {
        T val = 0;
        friend Node operator+(const Node &a, const Node &b) {
            return {a.val + b.val};
        }
        Node &operator=(const T &a) { return (this->val = a, *this); }
    };
    usize n;
    vector<Node> t;

  public:
    SegTree() : SegTree(0) {}
    SegTree(usize n) : n(n), t(2 * n) {}
    SegTree(const vector<T> &v) : SegTree(v.size()) {
        for (usize i = 0; i < n; i++)
            t[i + n] = v[i];
        for (usize i = n - 1; i > 0; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void update(usize p, T val) {
        for (t[p += n] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    T query(usize l, usize r) {
        Node resl, resr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = resl + t[l++];
            if (r & 1)
                resr = t[--r] + resr;
        }
        return (resl + resr).val;
    }
};

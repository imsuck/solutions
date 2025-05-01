#include <bits/stdc++.h>
using namespace std;

template<class M> struct SegTree {
    using T = typename M::T;

    int n;
    vector<T> t;

    SegTree() {}
    SegTree(int _n) : n(_n), t(2 * n, M::id()) {}
    SegTree(const vector<T> &v) : SegTree(int(v.size())) {
        copy_n(begin(v), n, begin(t) + n);
        for (int i = n; --i;) update(i);
    }

    T operator[](int p) const { return t[p + n]; }
    void set(int p, T x) {
        for (t[p += n] = x; p >>= 1;) update(p);
    }
    T operator()(int l, int r) const {
        T sml = M::id(), smr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }

    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};

using i64 = int64_t;

struct M {
    struct T {
        i64 sum = 0, pref = 0;
    };
    static T id() { return {}; }
    static T op(T l, T r) {
        return {l.sum + r.sum, max(l.pref, l.sum + r.pref)};
    }
};

using T = M::T;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<M::T> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].sum;
        a[i].pref = max<i64>(0, a[i].sum);
    }

    SegTree<M> st(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x, i--;
            st.set(i, {x, max(x, 0)});
        } else {
            int l, r;
            cin >> l >> r, l--;
            cout << st(l, r).pref << "\n";
        }
    }
}

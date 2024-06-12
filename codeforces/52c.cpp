#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

template<class S, class F> struct LazySegTree {
  public:
    LazySegTree() : LazySegTree(0) {}
    LazySegTree(int _n) : LazySegTree(vector<S>(_n, S::e())) {}
    LazySegTree(const vector<S> &v)
        : n((int)v.size()), lg(0), t(2 * n, S::e()), lz(n, F::id()) {
        while (1 << lg < n) lg++;
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n - 1; i >= 1; i--) update(i);
    }

    void set(int p, const S &x) {
        // assert(0 <= p && p < n);
        push_to(p);
        t[p + n] = x;
        update_from(p);
    }
    S get(int p) {
        // assert(0 <= p && p < n);
        push_to(p);
        return t[p + n];
    }

    S all_prod() { return prod(0, n); }
    S prod(int l, int r) {
        // assert(0 <= l && l <= r && r <= n);
        if (l == r) return S::e();
        push_to(l, r);
        S sml = S::e(), smr = S::e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = sml + t[l++];
            if (r & 1) smr = t[--r] + smr;
        }
        return sml + smr;
    }

    void apply(int p, const F &f) {
        // assert(0 <= p && p < n);
        push_to(p);
        t[p + n] = f(t[p + n]);
        update_from(p);
    }
    void apply(int l, int r, const F &f) {
        // assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        push_to(l, r);
        for (int l2 = l + n, r2 = r + n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        update_from(l, r);
    }

  private:
    int n, lg;
    vector<S> t;
    vector<F> lz;
    void update(int p) { t[p] = t[p << 1] + t[p << 1 | 1]; }
    void update_from(int p) {
        p += n;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    void update_from(int l, int r) {
        l += n, r += n;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; i++) update(l >> i);
        for (int i = ri + 1; i <= lg; i++) update(r >> i);
    }
    void all_apply(int p, const F &f) {
        t[p] = f(t[p]);
        if (p < n) lz[p] = f * lz[p];
    }
    void push(int p) {
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = F::id();
    }
    void push_to(int p) {
        p += n;
        for (int i = lg; i >= 1; i--) push(p >> i);
    }
    void push_to(int l, int r) {
        l += n, r += n;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = lg; i >= li + 1; i--) push(l >> i);
        for (int i = lg; i >= ri + 1; i--) push(r >> i);
    }
};

using i32 = int32_t;
using i64 = int64_t;

const i64 INF = 1e18;

struct S {
    i64 mn;
    static constexpr S e() { return S{INF}; }
    friend S operator+(const S &l, const S &r) { return S{min(l.mn, r.mn)}; }
};

struct F {
    i64 inc;
    static constexpr F id() { return F{0}; }
    friend F operator*(const F &l, const F &r) { return F{l.inc + r.inc}; }
    S operator()(const S &x) const { return S{x.mn + inc}; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 n;
    cin >> n;
    vector<S> v(n);
    for (S &s : v) cin >> s.mn;
    LazySegTree<S, F> st(v);
    i32 q;
    cin >> q;
    cin.ignore();
    while (q--) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        i32 l, r;
        i64 x = INF;
        ss >> l >> r >> x;
        if (x == INF) {
            if (r < l) {
                cout << (st.prod(l, n) + st.prod(0, r + 1)).mn << "\n";
                continue;
            }
            cout << st.prod(l, r + 1).mn << "\n";
        } else {
            if (r < l) {
                st.apply(l, n, F{x});
                st.apply(0, r + 1, F{x});
                continue;
            }
            st.apply(l, r + 1, F{x});
        }
    }
}

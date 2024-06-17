#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

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

struct S {
    i64 sum;
    i32 l, r;
    static S e() { return S{0, 0, 0}; }
    friend S operator+(const S &l, const S &r) {
        return S{l.sum + r.sum, l.l, r.r};
    }
};
struct F {
    i64 a, b;
    static F id() { return F{0, 0}; }
    friend F operator*(const F &l, const F &r) {
        return F{l.a + r.a, l.b + r.b};
    }
    S operator()(const S &x) const {
        return S{
            x.sum + (b * x.l - a) * (x.r - x.l + 1) + sum(x.r - x.l + 1) * b,
            x.l,
            x.r,
        };
    }
    static i64 sum(i64 n) { return n * (n + 1) / 2; }
};

void solve() {
    i32 n, q;
    cin >> n >> q;
    vec<S> v(n);
    for (i32 i = 0; i < n; i++) cin >> v[i].sum, v[i].l = v[i].r = i;
    LazySegTree<S, F> st(v);
    while (q--) {
        i32 ty, l, r;
        cin >> ty >> l >> r;
        l--;
        if (ty == 1)
            st.apply(l, r, F{l, 1});
        else
            cout << st.prod(l, r).sum << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}

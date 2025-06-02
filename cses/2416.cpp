#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

template<class M> struct LazySegTree {
    using T = typename M::T;
    using F = typename M::F;

    int n, lg, m;
    vector<T> t;
    vector<char> upd;
    vector<F> lz;

    LazySegTree() = default;
    LazySegTree(int _n) :
        n(_n), lg(_lg(n)), m(1 << lg), t(m * 2, M::id()), upd(m),
        lz(m, M::fid()) {}
    template<class V> LazySegTree(const V &v) : LazySegTree(int(v.size())) {
        copy(begin(v), end(v), begin(t) + m);
        for (int i = m; --i;) update(i);
    }

    T operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return M::id();
        int li = __builtin_ctz(l + m), ri = __builtin_ctz(r + m);
        push_to(l, li), push_to(r - 1, ri);
        T sml = M::id(), smr = M::id();
        for (l += m, r += m; l < r; l /= 2, r /= 2) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        int li = __builtin_ctz(l + m), ri = __builtin_ctz(r + m);
        push_to(l, li), push_to(r - 1, ri);
        for (int l2 = l + m, r2 = r + m; l2 < r2; l2 /= 2, r2 /= 2) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        update_from(l, li), update_from(r - 1, ri);
    }

  private:
    // clang-format off
    static int _lg(int n) { int l = 0; while (1 << l < n) l++; return l; }
    // clang-format on
    void update(int p) { t[p] = M::op(t[2 * p], t[2 * p + 1]); }
    void update_from(int p, int l = 0) {
        p += m;
        for (int i = l + 1; i <= lg; i++) update(p >> i);
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
        all_apply(2 * p, lz[p]), all_apply(2 * p + 1, lz[p]);
        lz[p] = M::fid(), upd[p] = false;
    }
    void push_to(int p, int l = 0) {
        p += m;
        for (int i = lg; i >= l + 1; i--) push(p >> i);
    }
};

using i64 = int64_t;

struct RangeSetRangeSum {
    struct T {
        i64 sum = 0;
        int sz = 0;
        T() {}
        T(i64 _sum, int _sz) : sum(_sum), sz(_sz) {}
        T(i64 x) : T(x, 1) {}
    };
    using F = int;

    static T id() { return {}; }
    static F fid() { return 0; }
    static T op(T l, T r) { return {l.sum + r.sum, l.sz + r.sz}; }
    static F comp(F l, F) { return l; }
    static bool map(F f, T &x) { return x.sum = i64(f) * x.sz, true; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1, 1.1e9), mx(2 * n);
    vector<i64> p(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p[i + 1] = p[i] + a[i];
        mx[i + n] = i;
    }

    auto argmx = [&](int i, int j) {
        return pair(a[i], i) > pair(a[j], j) ? i : j;
    };
    for (int i = n - 1; i > 0; i--) mx[i] = argmx(mx[2 * i], mx[2 * i + 1]);
    auto get = [&](int l, int r) {
        int ret = l;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) ret = argmx(ret, mx[l++]);
            if (r & 1) ret = argmx(mx[--r], ret);
        }
        return ret;
    };

    stack<int> st;
    st.push(n);
    LazySegTree<RangeSetRangeSum> lst(a);
    vector<i64> contrib(n);
    for (int i = n - 1; i >= 0; i--) {
        while (a[i] >= a[st.top()]) st.pop();
        int nxt = st.top();
        st.push(i);
        contrib[i] = i64(a[i]) * (nxt - i) - lst(i, nxt).sum;
        lst.apply(i, nxt, a[i]);
    }
    lst = {contrib};

    while (q--) {
        int l, r;
        cin >> l >> r, l--;
        int mxi = get(l, r);
        i64 ans = lst(l, mxi).sum;
        ans += i64(a[mxi]) * (r - mxi) - (p[r] - p[mxi]);
        cout << ans << "\n";
    }
}

#include <cassert>
#include <vector>
using namespace std;

// - S: S::e(), S::operator+
// - F: F::id(), F::operator*, const F(S)->S
template <class S, class F> struct LazySegTree {
  public:
    LazySegTree() : LazySegTree(0) {}
    LazySegTree(int _n) : LazySegTree(vector<S>(_n, S::e())) {}
    LazySegTree(const vector<S> &v) : n(v.size()) {
        m = 1, lg = 0;
        while (m < n)
            m *= 2, lg++;
        t = vector<S>(2 * m, S::e());
        lz = vector<F>(m, F::id());
        copy(begin(v), end(v), begin(t) + m);
        for (int i = m - 1; i >= 1; i--)
            update(i);
    }

    void set(int p, const S &x) {
        assert(0 <= p && p < n);
        push_to(p);
        t[p + m] = x;
        update_from(p);
    }
    S get(int p) {
        assert(0 <= p && p < n);
        push_to(p);
        return t[p + m];
    }

    S all_prod() const { return t[1]; }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return S::e();
        if (l == r + 1)
            return get(l);
        if (l == 0 && r == n)
            return all_prod();
        push_to(l, r);
        S resl = S::e(), resr = S::e();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resl = resl + t[l++];
            if (r & 1)
                resr = t[--r] + resr;
        }
        return resl + resr;
    }

    void apply(int p, const F &f) {
        assert(0 <= p && p < n);
        push_to(p);
        t[p + m] = f(t[p + m]);
        update_from(p);
    }
    void apply(int l, int r, const F &f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return;
        push_to(l, r);
        for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1)
                all_apply(l2++, f);
            if (r2 & 1)
                all_apply(--r2, f);
        }
        update_from(l, r);
    }

  private:
    int n, m, lg;
    vector<S> t;
    vector<F> lz;
    void update(int p) { t[p] = t[p << 1] + t[p << 1 | 1]; }
    void update_from(int p) {
        p += m;
        for (int i = 1; i <= lg; i++)
            update(p >> i);
    }
    void update_from(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; i++)
            update(l >> i);
        for (int i = ri + 1; i <= lg; i++)
            update(r >> i);
    }
    void all_apply(int p, const F &f) {
        t[p] = f(t[p]);
        if (p < m)
            lz[p] = f * lz[p];
    }
    void push(int p) {
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = F::id();
    }
    void push_to(int p) {
        p += m;
        for (int i = lg; i >= 1; i--)
            push(p >> i);
    }
    void push_to(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = lg; i >= li + 1; i--)
            push(l >> i);
        for (int i = lg; i >= ri + 1; i--)
            push(r >> i);
    }
};

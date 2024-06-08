#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using i64 = int64_t;
#define vec vector

const i32 MOD = 1e9 + 7;

template <class S, class F> struct LazySegTree {
  public:
    LazySegTree() : LazySegTree(0) {}
    LazySegTree(int _n) : LazySegTree(vec<S>(_n, S::e())) {}
    LazySegTree(const vec<S> &v) : n((int)v.size()) {
        m = 1, lg = 0;
        while (m < n) m *= 2, lg++;
        t = vec<S>(2 * m, S::e());
        lz = vec<F>(m, F::id());
        copy(v.begin(), v.end(), t.begin() + m);
        for (int i = m - 1; i >= 1; i--) update(i);
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

    S all_prod() { return t[1]; }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return S::e();
        if (l == r + 1) return get(l);
        if (l == 0 && r == n) return all_prod();

        push_to(l, r);
        S resl = S::e(), resr = S::e();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + t[l++];
            if (r & 1) resr = t[--r] + resr;
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
        if (l == r) return;

        push_to(l, r);
        for (int l2 = l + m, r2 = r + m; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        update_from(l, r);
    }

  private:
    int n, m, lg;
    vec<S> t;
    vec<F> lz;
    void update(int p) { t[p] = t[p << 1] + t[p << 1 | 1]; }
    void update_from(int p) {
        p += m;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    void update_from(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = li + 1; i <= lg; i++) update(l >> i);
        for (int i = ri + 1; i <= lg; i++) update(r >> i);
    }
    void all_apply(int p, const F &f) {
        t[p] = f(t[p]);
        if (p < m) lz[p] = f * lz[p];
    }
    void push(int p) {
        all_apply(p << 1, lz[p]), all_apply(p << 1 | 1, lz[p]);
        lz[p] = F::id();
    }
    void push_to(int p) {
        p += m;
        for (int i = lg; i >= 1; i--) push(p >> i);
    }
    void push_to(int l, int r) {
        l += m, r += m;
        int li = __builtin_ctz(l), ri = __builtin_ctz(r);
        for (int i = lg; i >= li + 1; i--) push(l >> i);
        for (int i = lg; i >= ri + 1; i--) push(r >> i);
    }
};

template<class T, int N, int mod> struct Matrix {
  private:
    template<class _> using vec = vector<_>;
    static constexpr T mul(T a, T b) { return mod ? a * b % mod : a * b; }

  public:
    T mat[N][N];
    T *operator[](int i) {
        assert(0 <= i && i < N);
        return mat[i];
    }
    constexpr Matrix() : mat{} {}
    Matrix(const vec<vec<T>> &v) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) mat[i][j] = v[i][j];
    }
    static constexpr Matrix id() {
        Matrix res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }

    constexpr friend Matrix operator*(const Matrix &l, const Matrix &r) {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    res[i][j] += mul(l.mat[i][k], r.mat[k][j]);
                    if (res[i][j] >= mod) res[i][j] -= mod;
                }
            }
        }
        return res;
    }
    Matrix operator^(int64_t n) const {
        Matrix res = id(), base = *this;
        while (n) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
    vec<T> operator*(const vec<T> &x) const {
        assert(x.size() == N);
        vec<T> res(x.size());
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                res[i] += mul(mat[i][k], x[k]);
                if (res[i] >= mod) res[i] -= mod;
            }
        }
        return res;
    }
};

using Mat = Matrix<i64, 2, MOD>;

Mat fib(int n) { return Mat{{{1, 1}, {1, 0}}} ^ n; }

struct S {
    vec<i64> v;
    static S e() { return S{{0, 0}}; }
    friend S operator+(const S &l, const S &r) {
        return S{{(l.v[0] + r.v[0]) % MOD, (l.v[1] + r.v[1]) % MOD}};
    }
};
struct F {
    Mat mat;
    static F id() { return F{Mat::id()}; }
    friend F operator*(const F &l, const F &r) { return F{l.mat * r.mat}; }
    S operator()(const S &x) const { return S{mat * x.v}; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vec<S> v(n);
    for (S &s : v) {
        int a;
        cin >> a;
        s.v = fib(a) * vec<i64>{1, 0};
    }
    LazySegTree<S, F> st(v);
    while (q--) {
        char ty;
        cin >> ty;
        if (ty == '1') {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            st.apply(l, r + 1, F{fib(x)});
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << st.prod(l, r + 1).v[1] << "\n";
        }
    }
}

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

template<class S> struct SegTree {
  public:
    SegTree() : SegTree(0) {}
    SegTree(int _n) : n(_n), t(2 * _n, S::e()) {}
    SegTree(const vector<S> &v) : SegTree((int)v.size()) {
        for (int i = 0; i < n; i++) t[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) update(i);
    }
    void set(int p, S val) {
        // assert(0 <= p && p < n);
        for (t[p += n] = val; p >>= 1;) update(p);
    }
    S get(int p) const {
        // assert(0 <= p && p < n);
        return t[p + n];
    }
    S all_prod() const { return t[1]; }
    S prod(int l, int r) const {
        // assert(0 <= l && l <= r && r <= n);

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
;

struct S {
    i64 sum = 0, mx = 0, l = 0, r = 0;
    static S e() { return S{}; }
    static S make(int n) { return S{n, max(n, 0), max(n, 0), max(n, 0)}; }
    friend S operator+(const S &l, const S &r) {
        return S{
            l.sum + r.sum,
            max({l.mx, r.mx, l.r + r.l}),
            max(l.l, l.sum + r.l),
            max(l.r + r.sum, r.r),
        };
    }
};

void solve() {
    i32 n, q;
    cin >> n >> q;
    vec<S> v(n);
    for (S &s : v) {
        int a;
        cin >> a;
        s = S::make(a);
    }
    SegTree<S> st(v);
    while (q--) {
        i32 l, r;
        cin >> l >> r;
        cout << st.prod(l - 1, r).mx << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}


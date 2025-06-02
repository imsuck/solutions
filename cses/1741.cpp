#include <bits/stdc++.h>
using namespace std;

template<class T = int> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    template<class... Ts> void push(Ts &...x) { (_push(x), ...); }
    void build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1;
        for (auto x : val) {
            if (og.empty() || og.back() != x) id++, og.push_back(x);
            x.get() = id;
        }
    }
    int size() const { return int(og.size()); }
    T operator[](int i) { return og[i]; }

  private:
    void _push(T &x) { val.push_back(x); }
    void _push(pair<T, T> &p) { push(p.first, p.second); }
    template<class V> void _push(V &v) {
        for (auto &x : v) _push(x);
    }
};

template<class M> struct LazySegTree {
    using T = typename M::T;
    using F = typename M::F;

    int n, lg = 0;
    vector<T> t;
    vector<F> lz;

    LazySegTree() {}
    LazySegTree(int _n) : n(_n), t(2 * n, M::id()), lz(n, M::fid()) {
        while (1 << lg < n) lg++;
    }
    template<class V> LazySegTree(const V &v) : LazySegTree(int(v.size())) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n; --i;) update(i);
    }

    T all_prod() const { return t[1]; }
    void apply(int l, int r, const F &f) {
        int li = __builtin_ctz(l + n), ri = __builtin_ctz(r + n);
        push_to(l, li), push_to(r - 1, ri);
        for (int l2 = l + n, r2 = r + n; l2 < r2; l2 /= 2, r2 /= 2) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
        }
        update_from(l, li), update_from(r - 1, ri);
    }

  private:
    void update(int p) { t[p] = M::op(t[2 * p], t[2 * p + 1]); }
    void update_from(int p, int l = 0) {
        p += n;
        for (int i = l + 1; i <= lg; i++) update(p >> i);
    }
    void all_apply(int p, const F &f) {
        t[p] = M::map(f, t[p]);
        if (p < n) lz[p] = M::comp(f, lz[p]);
    }
    void push(int p) {
        all_apply(2 * p, lz[p]), all_apply(2 * p + 1, lz[p]);
        lz[p] = M::fid();
    }
    void push_to(int p, int l = 0) {
        p += n;
        for (int i = lg; i >= l + 1; i--) push(p >> i);
    }
};

struct RectUnion {
    using Rect = tuple<int, int, int, int>;
    using Event = tuple<int, int, int>;
    struct MinCount {
        struct T {
            int mn = numeric_limits<int>::max(), cnt = 0;
        };
        using F = int;
        static T id() { return {}; }
        static F fid() { return 0; }
        static T op(T l, T r) {
            if (l.mn < r.mn) return l;
            if (r.mn < l.mn) return r;
            return {l.mn, l.cnt + r.cnt};
        }
        static F comp(F l, F r) { return l + r; }
        static T map(F f, T x) { return {x.mn + f, x.cnt}; }
    };

    int n;
    vector<Rect> rects;

    RectUnion(int _n) : n(_n) { rects.reserve(n); }

    void add_rect(int l, int d, int r, int u) {
        rects.emplace_back(l, d, r, u);
    }
    int64_t run() {
        Compressor xs, ys;
        for (auto &[l, d, r, u] : rects) xs.push(l, r), ys.push(d, u);
        xs.build(), ys.build();

        vector<vector<Event>> ev(xs.size());
        for (auto [l, d, r, u] : rects) {
            ev[l].emplace_back(d, u, 1);
            ev[r].emplace_back(d, u, -1);
        }
        vector<MinCount::T> init(ys.size() - 1);
        for (int i = 0; i + 1 < ys.size(); i++)
            init[i] = {0, ys[i + 1] - ys[i]};
        LazySegTree<MinCount> st(init);

        int64_t res = 0, len_y = ys.og.back() - ys[0];
        for (int i = 0; i + 1 < ev.size(); i++) {
            for (auto [d, u, diff] : ev[i]) st.apply(d, u, diff);
            auto [mn, cnt] = st.all_prod();
            if (mn > 0) cnt = 0;
            res += (len_y - cnt) * (xs[i + 1] - xs[i]);
        }
        return res;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    RectUnion solver(n);
    for (int i = 0; i < n; i++) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        solver.add_rect(l, d, r, u);
    }
    cout << solver.run() << "\n";
}

// O(nlog(n))
#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

template<class T> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    template<class... Ts> void push(Ts &...x) { (val.push_back(x), ...); }
    void build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1, prv = -1;
        for (auto &x : val) {
            if (prv != x) {
                id++, prv = x;
                og.push_back(x);
            }
            x.get() = id;
        }
    }
    int size() const { return int(og.size()); }
    T operator[](int i) const { return og[i]; }
    bool find(T x) const { return binary_search(begin(og), end(og), x); }
};

struct Fenwick {
    int n;
    vector<i64> t;

    Fenwick(int _n) : n(_n), t(n + 1) {}

    void add(int p, int d) {
        for (p++; p <= n; p += p & -p) t[p] += d;
    }
    i64 prod(int r) const {
        i64 sum = 0;
        for (; r; r &= r - 1) sum += t[r];
        return sum;
    }
    i64 prod(int l, int r) const { return prod(r) - prod(l); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    Compressor<int> comp;
    struct event {
        int type, x, a, b, c;
    };
    vector<event> evs(n + 2 * q);
    for (int i = 0, x; i < n; i++) {
        cin >> x, x--;
        evs[i] = {2, i, x, 1, 0};
        comp.push(evs[i].a);
    }
    for (int i = 0; i < q; i++) {
        int l, r, d, u;
        cin >> l >> r >> d >> u, l--, d--;
        int j = 2 * i + n;
        evs[j] = {0, l, d, u, i};
        evs[j + 1] = {1, r, d, u, i};
        comp.push(evs[j].a, evs[j].b);
        comp.push(evs[j + 1].a, evs[j + 1].b);
    }
    comp.build();
    sort(begin(evs), end(evs), [](auto &a, auto &b) {
        return pair(a.x, a.type) < pair(b.x, b.type);
    });

    Fenwick t(comp.size());
    vector<i64> ans(q);
    for (auto [type, x, a, b, c] : evs) {
        if (type == 0) {
            ans[c] -= t.prod(a, b);
        } else if (type == 1) {
            ans[c] += t.prod(a, b);
        } else {
            t.add(a, b);
        }
    }

    for (auto &i : ans) cout << i << "\n";
}

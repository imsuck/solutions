#include <bits/stdc++.h>
using namespace std;

template<class T> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    void push(T &x) { val.push_back(x); }
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

const int B = 450;
struct microsoft_paint {
    int n;
    vector<int> cnt, blk;

    microsoft_paint(int _n) : n(_n), cnt(n), blk(n / B + 1) {}

    void add(int p) { cnt[p]++, blk[p / B]++; }
    void del(int p) { cnt[p]--, blk[p / B]--; }
    int get(int l, int r) {
        int bl = l / B, br = r / B;
        int ret = 0;
        if (bl == br) {
            for (int i = l; i < r; i++) ret += cnt[i];
            return ret;
        }
        for (int i = l; i < min(r, (bl + 1) * B); i++) ret += cnt[i];
        for (int i = bl + 1; i < br; i++) ret += blk[i];
        for (int i = max(l, br * B); i < r; i++) ret += cnt[i];
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Compressor<int> comp;

    int n, q;
    cin >> n >> q;
    vector<int> x(n), ans(q);
    for (int &i : x) cin >> i, comp.push(i);
    vector<int> a(q), b(q), c(q), d(q), qi(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        a[i]--, d[i]++, qi[i] = i;
        comp.push(c[i]), comp.push(d[i]);
    }
    comp.build();

    sort(begin(qi), end(qi), [&](int i, int j) {
        int li = a[i], ri = b[i], lj = a[j], rj = b[j];
        int bi = li / B, bj = lj / B;
        if (bi != bj) return bi < bj;
        if (ri != rj) return (bi & 1) != (ri < rj);
        return li < lj;
    });

    microsoft_paint msp(comp.size());
    int ql = 0, qr = 0;
    for (int i : qi) {
        int li = a[i], ri = b[i];
        while (li < ql) msp.add(x[--ql]);
        while (qr < ri) msp.add(x[qr++]);
        while (ql < li) msp.del(x[ql++]);
        while (ri < qr) msp.del(x[--qr]);
        ans[i] = msp.get(c[i], d[i]);
    }

    for (int i : ans) cout << i << "\n";
}

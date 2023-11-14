#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;

struct FenwickTree {
    vector<i64> bit;
    i32 n;

    FenwickTree(i32 n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<i32> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    i64 sum(i32 r) {
        i64 s = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            s += bit[r];
        return s;
    }

    i64 sum(i32 l, i32 r) { return sum(r) - sum(l - 1); }

    void add(i32 idx, i32 delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

int main() {
    i32 n, q;
    cin >> n >> q;

    FenwickTree bit(n);
    for (i32 i = 0; i < n; i++) {
        i32 a;
        cin >> a;
        bit.add(i, a);
    }

    while (q--) {
        i32 t, a, b;
        cin >> t >> a >> b, a--;
        if (t == 1) {
            i32 diff = b - bit.sum(a, a);
            bit.add(a, diff);
        } else {
            cout << bit.sum(a, b - 1) << "\n";
        }
    }
}
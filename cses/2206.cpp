// Idea: Handle `j < i` and `i <= j` separately
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> t;

    SegTree(int _n) : n(_n), t(2 * n, 1.1e9) {}

    void set(int p, int x) {
        for (t[p += n] = x; p /= 2;) t[p] = min(t[2 * p], t[2 * p + 1]);
    }
    int prod(int l, int r) const {
        int mn = 1.1e9;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) mn = min(mn, t[l++]);
            if (r & 1) mn = min(mn, t[--r]);
        }
        return mn;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    SegTree st1(n), st2(n);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        st1.set(i, x - (i + 1)), st2.set(i, x + (i + 1));
    }
    while (q--) {
        int t, i, x;
        cin >> t >> i, i--;
        if (t == 1) {
            cin >> x;
            st1.set(i, x - (i + 1)), st2.set(i, x + (i + 1));
        } else {
            cout << min(st1.prod(0, i + 1) + (i + 1), st2.prod(i, n) - (i + 1))
                 << "\n";
        }
    }
}

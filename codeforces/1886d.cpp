#include <bits/stdc++.h>
using namespace std;
#include "library/ds/segtree.hpp"
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

#define fn auto
using mint = modint998;

struct M {
    using T = mint;
    static T id() { return 1; }
    static T op(T l, T r) { return l * r; }
};

fn solve() {
    i32 n, q;
    str s;
    cin >> n >> q >> s;
    SegTree<M> st(n - 1, [&](i32 i) {
        if (s[i] == '<' || s[i] == '>') return 1;
        return i;
    });
    cout << st.all_prod() << "\n";
    while (q--) {
        i32 p;
        char c;
        cin >> p >> c, p--;
        st[p] = (c == '<' || c == '>') ? 1 : p;
        cout << st.all_prod() << "\n";
    }
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

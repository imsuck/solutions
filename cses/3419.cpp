#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

struct mex_set {
    set<i32> s;
    unordered_map<i32, i32> c;
    mex_set(i32 n) {
        for (i32 i = 0; i <= n; i++) s.insert(i);
    }
    void insert(i32 x) {
        if (!c[x]++) s.erase(x);
    }
    void erase(i32 x) {
        if (!--c[x]) s.insert(x);
        c[x] = max(c[x], 0);
    }
    i32 get() const { return *s.begin(); }
};

void solve() {
    i32 n;
    cin >> n;
    vec<vec<i32>> a(n, vec<i32>(n));
    mex_set mex(n * n);
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < n; j++) {
            for (i32 k = 0; k < i; k++) mex.insert(a[k][j]);
            for (i32 k = 0; k < j; k++) mex.insert(a[i][k]);

            cout << (a[i][j] = mex.get()) << " \n"[j == n - 1];

            for (i32 k = 0; k < i; k++) mex.erase(a[k][j]);
            for (i32 k = 0; k < j; k++) mex.erase(a[i][k]);
        }
    }
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

const i64 inf = 1LL << 60;

struct matrix {
    vec<vec<i64>> m;
    matrix(i32 _n, i64 x = inf) : m(_n, vec<i64>(_n, x)) {}
    auto &operator[](i32 i) { return m[i]; }
    auto &operator[](i32 i) const { return m[i]; }

    matrix operator*(const matrix &b) {
        matrix c(n());
        for (i32 i = 0; i < n(); i++)
            for (i32 k = 0; k < n(); k++)
                for (i32 j = 0; j < n(); j++)
                    c[i][j] = min(c[i][j], m[i][k] + b[k][j]);
        return c;
    }
    matrix &operator*=(const matrix &b) { return *this = *this * b; }
    matrix pow(i32 k) {
        bool ya = 0;
        matrix r(0), x = *this;
        for (; k; k >>= 1, x *= x)
            if (k & 1) exchange(ya, 1) ? r *= x : r = x;
        return r;
    }

    i32 n() const { return (i32)m.size(); }
};

void solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
    matrix mat(n);
    for (i32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        mat[u][v] = min<i64>(mat[u][v], w);
    }
    mat = mat.pow(k);
    i64 ans = mat[0][n - 1];
    cout << (ans < inf ? ans : -1) << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

using mint = modint107;

struct Matrix {
    vec<vec<mint>> mat;

    Matrix(i32 _n, i32 _m) : mat(_n, vec<mint>(_m)) {}

    enum gauss_mode { normal, reverse };
    template<gauss_mode mode = normal> Matrix &gauss() {
        auto reduce = [](auto &a, const auto &b) {
            i32 pivot = 0;
            while (pivot < b.size() && b[pivot] == 0) pivot++;
            if (pivot >= b.size()) return;
            mint factor = a[pivot] * b[pivot].inv();
            for (i32 i = pivot; i < a.size(); i++) a[i] -= factor * b[i];
        };
        for (i32 i = 0; i < n(); i++)
            for (i32 j = (mode == normal) * i; j < n(); j++)
                if (i != j) reduce(mat[j], mat[i]);
        return *this;
    }

    i32 n() const { return (i32)mat.size(); }
    i32 m() const { return (i32)mat[0].size(); }
    auto &operator[](i32 i) { return mat[i]; }
};

void solve() {
    i32 n, m;
    cin >> n >> m;
    Matrix mat(n, m + 1);
    for (i32 i = 0; i < n; i++)
        for (i32 j = 0; j <= m; j++) cin >> mat[i][j];
    mat.gauss();
    vec<mint> xs(m);
    for (i32 i = n - 1; i >= 0; i--) {
        i32 piv = -1;
        mint x = mat[i][m];
        for (i32 j = m - 1; j >= 0; j--) {
            x -= xs[j] * mat[i][j];
            if (mat[i][j] != 0) piv = j;
        }
        if (piv != -1) xs[piv] = x / mat[i][piv];
    }
    // I'm stoopid
    for (i32 i = 0; i < n; i++) {
        mint sm = 0;
        for (i32 j = 0; j < m; j++) sm += mat[i][j] * xs[j];
        if (sm != mat[i][m]) {
            cout << "-1\n";
            return;
        }
    }
    for (i32 i = 0; i < m; i++) cout << xs[i] << " \n"[i == m - 1];
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

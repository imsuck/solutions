#include <bits/stdc++.h>
using namespace std;

#include "ds/segtree.hpp"
#include "math/modint.hpp"

using mint = modint998;

template<size_t N> struct matrix {
    array<array<mint, N>, N> mat;

    auto &operator[](int i) { return mat[i]; }
    auto &operator[](int i) const { return mat[i]; }

    matrix() { mat.fill({}); }
    matrix(const vector<vector<mint>> &v) {
        assert(v.size() == N);
        for (int i = 0; i < N; i++) {
            assert(v[i].size() == N);
            for (int j = 0; j < N; j++) mat[i][j] = v[i][j];
        }
    }
    static matrix id() {
        matrix res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }

    friend matrix operator*(const matrix &a, const matrix &b) {
        matrix c;
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++) c[i][j] += a[i][k] * b[k][j];
        return c;
    }
    matrix &operator+=(const matrix &b) { return *this = +this + b; }
    matrix &operator*=(const matrix &b) { return *this = *this * b; }
    array<mint, N> operator*(const array<mint, N> &a) {
        array<mint, N> res{};
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++) res[i] += mat[i][k] * a[k];
        return res;
    }
};

struct Monoid {
    using T = matrix<3>;
    static T id() { return T::id(); }
    static T op(const T &l, const T &r) { return r * l; }
};

using T = Monoid::T;

struct Line {
    // ax + by + c = 0
    mint a, b, c;
};

pair<mint, mint> sle(const Line &d1, const Line &d2) {
    // gotta transform to ax + by = c (negate c)
    mint dx = -(d1.c * d2.b - d2.c * d1.b);
    mint dy = -(d1.a * d2.c - d2.a * d1.c);
    mint d = d1.a * d2.b - d2.a * d1.b;
    return {dx / d, dy / d};
}

T get_matrix(Line d, bool diamond) {
    auto [dx, dy] = sle(Line{d.b, -d.a, 0}, d);
    T do_offset = {{
        {1, 0, -dx},
        {0, 1, -dy},
        {0, 0, 1},
    }};
    T undo_offset = {{
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1},
    }};

    d.c = 0;
    auto [ix, iy] = sle(Line{d.b, -d.a, -d.b}, d);
    auto [jx, jy] = sle(Line{d.b, -d.a, d.a}, d);

    if (diamond) {
        ix = 2 * ix - 1, iy = 2 * iy;
        jx = 2 * jx, jy = 2 * jy - 1;
    }

    T f = {{
        {ix, jx, 0},
        {iy, jy, 0},
        {0, 0, 1},
    }};

    return undo_offset * f * do_offset;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    SegTree<Monoid> st(n, [](int) {
        char tp;
        int a, b, c;
        cin >> tp >> a >> b >> c;
        return get_matrix(Line{a, b, c}, tp == 'D');
    });

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            char tp;
            int j, a, b, c;
            cin >> j >> tp >> a >> b >> c, j--;
            st[j] = get_matrix(Line{a, b, c}, tp == 'D');
        } else {
            int x, y, l, r;
            cin >> x >> y >> l >> r, l--;
            auto f = st(l, r);
            auto res = f * array<mint, 3>{x, y, 1};
            cout << res[0] << " " << res[1] << "\n";
        }
    }
}

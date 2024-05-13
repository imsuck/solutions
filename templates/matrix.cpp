#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;
using i64 = int64_t;
template <typename T> using vec = vector<T>;

const i32 MOD = 1e9 + 7;

// TODO: Make this work for n*m matrices
template<typename T, T mod> struct Matrix {
    vec<vec<T>> mat;
    Matrix() : mat(2, vec<T>(2)) {}
    Matrix(vec<vec<T>> &v) : mat(v) {}
    Matrix(vec<vec<T>> v) : mat(v) {}
    vec<T> &operator[](i32 i) { return mat[i]; }
    friend Matrix operator*(Matrix &a, Matrix &b) {
        Matrix res;
        for (i32 i = 0; i < 2; i++) {
            for (i32 j = 0; j < 2; j++) {
                for (i32 k = 0; k < 2; k++) {
                    res[i][j] += a[i][k] * b[k][j];
                    if (mod) res[i][j] %= mod;
                }
            }
        }
        return res;
    }
    Matrix operator^(T n) {
        Matrix A = *this, res = A;
        while (n) {
            if (n % 2 != 0)
                res = res * A;
            A = A * A;
            n /= 2;
        }
        return res;
    }
};

void solve() {
    i64 n;
    cin >> n;
    cout << (Matrix<i64, MOD>({{1, 1}, {1, 0}}) ^ n)[1][1] << "\n";
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

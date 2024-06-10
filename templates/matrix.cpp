#include <cassert>
#include <cstdint>
#include <vector>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;

// TODO: Make this work for n*m matrices
template<class T, int N, int mod> struct Matrix {
  private:
    template<class _> using vec = vector<_>;
    static constexpr T mul(T a, T b) { return mod ? a * b % mod : a * b; }

  public:
    T mat[N][N];
    T *operator[](int i) {
        // assert(0 <= i && i < N);
        return mat[i];
    }
    constexpr Matrix() : mat{} {}
    constexpr Matrix(const vec<vec<T>> &v) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) mat[i][j] = v[i][j];
    }
    static constexpr Matrix id() {
        Matrix res;
        for (int i = 0; i < N; i++) res[i][i] = 1;
        return res;
    }

    constexpr friend Matrix operator*(const Matrix &l, const Matrix &r) {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    res[i][j] += mul(l.mat[i][k], r.mat[k][j]);
                    if (res[i][j] >= mod) res[i][j] -= mod;
                }
            }
        }
        return res;
    }
    Matrix operator^(int64_t n) const {
        // assert(n >= 0);
        Matrix res = id(), base = *this;
        while (n) {
            if (n & 1) res = res * base;
            base = base * base;
            n >>= 1;
        }
        return res;
    }
    vec<T> operator*(const vec<T> &x) const {
        // assert(x.size() == N);
        vec<T> res(x.size());
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                res[i] += mul(mat[i][k], x[k]);
                if (res[i] >= mod) res[i] -= mod;
            }
        }
        return res;
    }
};

// ----------------------------------------------------------------------------
#include <iostream>

const i32 MOD = 1e9 + 7;

void solve() {
    i64 n;
    cin >> n;
    cout << (Matrix<i64, 2, MOD>({{1, 1}, {1, 0}}) ^ n)[1][0] << "\n";
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

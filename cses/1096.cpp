#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

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

const i32 MOD = (i32)1e9 + 7;

using Mat = Matrix<i64, 6, MOD>;

void solve() {
    i64 n;
    cin >> n;
    Mat base{{
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
    }};
    vec<i64> v{16, 8, 4, 2, 1, 1};
    cout << ((base ^ n) * v)[5] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}

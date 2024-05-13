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
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

const i32 MOD = 1e9 + 7;

struct Matrix {
    i32 n;
    vec<vec<i64>> mat;
    Matrix(i32 n) : n(n), mat(n, vec<i64>(n)) {}
    static Matrix id(i32 n) {
        Matrix res(n);
        for (i32 i = 0; i < n; i++)
            res[i][i] = 1;
        return res;
    }
    vec<i64> &operator[](i32 i) { return mat[i]; }
    friend Matrix operator*(Matrix &a, Matrix &b) {
        i32 n = a.n;
        Matrix res(n);
        for (i32 i = 0; i < n; i++)
            for (i32 j = 0; j < n; j++) 
                for (i32 k = 0; k < n; k++)
                    res[i][j] += a[i][k] * b[k][j] % MOD, res[i][j] %= MOD;
        return res;
    }
    Matrix operator^(i32 p) {
        Matrix A = *this, res = id(n);
        while (p) {
            if (p & 1)
                res = res * A;
            A = A * A;
            p /= 2;
        }
        return res;
    }
};

void solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
    Matrix g(n);
    while (m--) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g.mat[u][v]++;
    }
    cout << (g^k)[0][n-1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}

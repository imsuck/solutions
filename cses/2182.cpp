#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) 42
#endif

using i64 = int64_t;
#define vec vector

const int MOD = int(1e9 + 7);

int inv(int a, int m = MOD) {
    int b = m, x = 1, y = 0;
    while (b) {
        x = exchange(y, x - a / b * y);
        a = exchange(b, a % b);
    }
    assert(a == 1);
    return x < 0 ? x + m : x;
}
int add(int a, int b, int m = MOD) { return (a + b) % m; }
int sub(int a, int b, int m = MOD) { return add(a, m - b); }
int mul(int a, int b, int m = MOD) { return int((i64)a * b % m); }
int pow(int a, int n, int m = MOD) {
    int r = 1;
    while (n) n & 1 ? r = mul(r, a, m) : 0, a = mul(a, a, m), n >>= 1;
    return r;
}

int s(int p, int n) { return mul(sub(pow(p, n + 1), 1), inv(sub(p, 1))); }
int sum_n(int n, int m) { return int((i64)n * (n + 1) / 2 % m); }

void solve() {
    int n;
    cin >> n;
    int sigma = 1, sigma2 = 1;
    int sum = 1, prod = 1;
    for (int i = 0, p, k; i < n; i++) {
        cin >> p >> k;
        sigma = mul(sigma, k + 1);
        sum = mul(sum, s(p, k));
        prod = mul(pow(prod, k + 1),
                   pow(p, mul(sum_n(k, MOD - 1), sigma2, MOD - 1)));
        sigma2 = mul(sigma2, k + 1, MOD - 1);
    }
    cout << sigma << " " << sum << " " << prod << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}

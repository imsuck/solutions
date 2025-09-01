#include <bits/stdc++.h>
using namespace std;

using f96 = long double;
using f128 = __float128;

f128 abs128(f128 x) { return x < 0 ? -x : x; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> r(n);
    f128 res = 0;
    auto calc = [](int l, int r) {
        if (l <= r) return (l - 1) * l / 2;
        return (r - 1) * r / 2 + (l - r) * r;
    };
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        for (int j = 0; j < i; j++)
            res += calc(r[j], r[i]) / f128(r[j] * r[i]);
    }
    res *= 1e6;
    long i = long(f96(res));
    f128 d = res - i;
    constexpr f128 half = 1 / f128(2);
    if (abs128(d - half) < 1e-20) {
        if (i % 2 == 0) res = i;
        else res = i + 1;
    } else {
        res -= d - (d > half);
    }
    cout << fixed << setprecision(6) << f96(res) / 1e6 << "\n";
}

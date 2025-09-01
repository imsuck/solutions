#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

using mint = modint107;

i32 main() {
    i32 n, k;
    cin >> n >> k;
    vec<mint> fac(n + 1, 1);
    for (i32 i = 1; i <= n; i++) fac[i] = i * fac[i - 1];
    auto comb = [&](i32 _n, i32 _k) -> mint {
        if (_k < 0 || _n < _k) return 0;
        return fac[_n] / (fac[_n - _k] * fac[_k]);
    };
    mint ans = mint(k).pow(n);
    for (i32 i = 1, sg = 1; i <= k - 1; i++, sg = -sg)
        ans -= sg * comb(k, i) * mint(k - i).pow(n);
    cout << ans << "\n";
}

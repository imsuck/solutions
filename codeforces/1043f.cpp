#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto

const i32 N = (i32)3e5 + 1;
const i32 mod = (i32)1e9 + 7;
i32 sub(i32 a, i32 b) { return (a -= b) < 0 ? a + mod : a; }
i32 mul(i64 a, i32 b) { return a * b % mod; }
i32 inv(i32 a) {
    i32 b = mod, x = 1, y = 0;
    while (b) {
        i32 d = a / b;
        x = exchange(y, x - d * y);
        a = exchange(b, a - d * b);
    }
    assert(a == 1);
    return x < 0 ? x + mod : x;
}

fn solve() {
    vec<i32> fac(N);
    fac[0] = 1;
    for (i32 i = 1; i < N; i++) fac[i] = mul(i, fac[i - 1]);
    auto comb = [&](i32 n, i32 k) {
        if (k < 0 || n < k) return 0;
        return mul(fac[n], inv(mul(fac[n - k], fac[k])));
    };

    i32 n;
    cin >> n;
    vec<i32> muls(N);
    for (i32 i = 0, a; i < n; i++) cin >> a, muls[a]++;

    for (i32 i = 1; i < N; i++)
        for (i32 j = 2 * i; j < N; j += i) muls[i] += muls[j];

    vec<i32> ways(N);
    for (i32 sz = 1; sz <= 7; sz++) {
        for (i32 i = 1; i < N; i++) ways[i] = comb(muls[i], sz);
        for (i32 i = N - 1; i >= 1; i--)
            for (i32 j = 2 * i; j < N; j += i) ways[i] = sub(ways[i], ways[j]);

        if (ways[1]) {
            cout << sz << "\n";
            return;
        }
    }
    cout << "-1\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

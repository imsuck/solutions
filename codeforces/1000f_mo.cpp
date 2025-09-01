#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/mo.hpp"
#include "library/other/types.hpp"

// ~2900ms, yeah very slow

void solve() {
    const i32 N = (i32)5e5 + 1;
    const i32 B = N / (i32)sqrt(N);

    i32 n, q;
    cin >> n;
    vec<i32> a(n);
    for (i32 &i : a) cin >> i;
    cin >> q;
    vec<pair<i32, i32>> qs(q);
    for (auto &[l, r] : qs) cin >> l >> r, l--;
    Mo mo(n, qs);

    vec<i32> cnt(N), blk(B + 1);
    vec<bool> once(N);
    auto get = [&]() {
        for (i32 b = 0; b <= B; b++)
            if (blk[b])
                for (i32 i = b * B;; i++)
                    if (once[i]) return i;
        return 0;
    };
    auto add = [&](i32 x) {
        cnt[x]++;
        if (cnt[x] == 1) {
            once[x] = 1, blk[x / B]++;
        } else if (cnt[x] == 2) {
            once[x] = 0, blk[x / B]--;
        }
    };
    auto del = [&](i32 x) {
        cnt[x]--;
        if (cnt[x] == 1) {
            once[x] = 1, blk[x / B]++;
        } else if (cnt[x] == 0) {
            once[x] = 0, blk[x / B]--;
        }
    };

    vec<i32> ans(q);
    mo.run(
        [&](i32 i) { ans[i] = get(); },
        [&](i32 i) { add(a[i]); },
        [&](i32 i) { del(a[i]); }
    );

    for (i32 i : ans) cout << i << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

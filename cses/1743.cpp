#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

void solve() {
    str s;
    cin >> s;
    i32 n = (i32)s.size();
    array<i32, 127> cnt{};
    for (char c : s) cnt[c]++;
    s = "$";
    for (i32 i = 0; i < n; i++) {
        for (char j = 'A'; j <= 'Z'; j++) {
            if (cnt[j] < 1 || s.back() == j) continue;
            cnt[j]--;
            i32 m = n - i - 1;

            bool good = true;
            for (char k = 'A'; k <= 'Z'; k++) {
                i32 sz = j == k ? m - 1 : m;
                good &= 2 * cnt[k] <= sz + 1;
            }
            if (good) {
                s += j;
                break;
            }

            cnt[j]++;
        }
    }
    cout << (s.size() > 1 ? s.substr(1, n) : "-1") << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

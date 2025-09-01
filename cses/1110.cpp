#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    str s;
    cin >> s;
    s += s;
    i32 n = (i32)s.size(), i = 0, ans = 0;
    for (; i < n / 2;) {
        ans = i;
        i32 j = i + 1, k = i;
        for (; j < n && s[k] <= s[j]; j++) k = s[k] < s[j] ? i : k + 1;
        while (i <= k) i += j - k;
    }
    cout << s.substr(ans, n / 2) << "\n";
}

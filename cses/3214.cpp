#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

// gcd(a, b) = gcd(a, a + b) = gcd(a, a - b)

void solve() {
    i32 a, b, x;
    cin >> a >> b >> x;
    cout << (x % gcd(a, b) == 0 && x <= a ? "YES" : "NO") << "\n";
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) solve();
}

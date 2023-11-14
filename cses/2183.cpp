#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i64 = int64_t;

void solve() {
    i64 n;
    cin >> n;
    vector<i64> v(n);
    for (i64 &i : v) {
        cin >> i;
    }
    sort(v.begin(), v.end());
    i64 cur = 1, s = 0;
    for (i64 i : v) {
        if (cur < i) {
            cout << cur << "\n";
            return;
        }
        cur = (s += i) + 1;
    }
    cout << cur << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

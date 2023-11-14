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
    i64 med = v[n/2];
    i64 cost = 0;
    for (i64 i : v) {
        cost += abs(i - med);
    }
    cout << cost << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

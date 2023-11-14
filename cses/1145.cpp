#pragma GCC optimize("Ofast,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m = 1, j, i = 0;
    cin >> n;
    vector<int> a(n), d(2e5 + 9, 1e9 + 9);
    d[0] = -1e9 - 9;
    for (; i < n; i++) {
        cin >> a[i];
        j = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        d[j] = a[i];
        m = max(m, j);
    }
    cout << m << "\n";
}

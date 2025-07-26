#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, mx = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    int l = 0, m;
    while (1 << l < mx) l++;
    m = 1 << l;
    vector<int> sub(m), sup(m);
    for (auto i : a) sub[i]++, sup[i]++;

    for (int i = 0; i < l; i++) {
        for (int mask = 1; mask < m; mask++) {
            if (mask >> i & 1) {
                sub[mask] += sub[mask ^ 1 << i];
                sup[mask ^ 1 << i] += sup[mask];
            }
        }
    }
    for (int i : a)
        cout << sub[i] << " " << sup[i] << " " << n - sub[i ^ (m - 1)] << "\n";
}

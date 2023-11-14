#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k, c = 0;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (int &_ : a) {
        cin >> _;
    }
    for (int &_ : b) {
        cin >> _;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0, j = 0; i < n && j < m; i++) {
        while (j + 1 < m && a[i] - b[j] > k) {
            j++;
        }
        c += abs(a[i] - b[j]) <= k ? j++, 1 : 0;
    }
    cout << c << "\n";
}

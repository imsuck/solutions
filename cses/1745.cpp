#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x;
    cin >> n;
    bitset<100005> dp(1);
    for (int i = 0; i < n; i++) {
        cin >> x;
        dp |= dp << x;
    }
    cout << dp.count() - 1 << "\n";
    for (int i = 1; i < 100005; i++) {
        if (dp[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
}

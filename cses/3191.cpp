#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<int> basis;
    auto add = [&](int x) {
        for (int b : basis) x = min(x, x ^ b);
        if (x) basis.push_back(x);
    };
    int n;
    cin >> n;
    for (int i = 0, a; i < n; i++) cin >> a, add(a);
    int ans = 0;
    for (int b : basis) ans = max(ans, ans ^ b);
    cout << ans << "\n";
}

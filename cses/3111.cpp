#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<array<int, 3>> e(n - 1);
    for (auto &[w, u, v] : e) cin >> u >> v >> w, u--, v--;
    sort(rbegin(e), rend(e));
    int64_t ans = 0;
    vector<int> d(n, -1);
    auto f = [&](int v) {
        while (d[v] >= 0) v = d[d[v]] < 0 ? d[v] : d[v] = d[d[v]];
        return v;
    };
    for (auto [w, u, v] : e) {
        ans += 1LL * w * d[u = f(u)] * d[v = f(v)];
        if (d[u] > d[v]) swap(u, v);
        d[u] += d[v], d[v] = u;
    }
    cout << ans << "\n";
}

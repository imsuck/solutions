#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

void solve() {
    int n;
    cin >> n;
    // vec<int> g[n + 1];
    vec<pair<int, int>> g;
    bool drawn[n + 1];
    fill_n(drawn, n + 1, false);
    drawn[1] = true;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g.emplace_back(u, v);
        // g[u].push_back(v);
    }
    int cnt = 0;
    bool fin = false;
    while (!fin) {
        fin = true;
        for (int i = 0; i < n - 1; i++) {
            if (drawn[g[i].first]) {
                drawn[g[i].second] = true;
            } else {
                fin = false;
            }
        }
        cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}

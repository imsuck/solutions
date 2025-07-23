#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;

template<class I> const I inf = numeric_limits<I>::max();

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> e(m);
    for (auto &[u, v, w] : e) cin >> u >> v >> w, u--, v--;
    int x = -1;
    vector<i64> d(n);
    vector<bool> vis(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto &[u, v, w] : e)
            if (d[u] < inf<i64> && d[v] > d[u] + w)
                d[v] = min(inf<i64> / 2, d[u] + w), p[v] = u, x = v;
    }
    if (x == -1) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) x = p[x];
    vector<int> cycl{x};
    for (int y = p[x]; y != x; y = p[y]) cycl.push_back(y);
    cycl.push_back(x);
    reverse(begin(cycl), end(cycl));
    for (int i = 0; i < cycl.size(); i++)
        cout << cycl[i] + 1 << " \n"[i == cycl.size() - 1];
}

#include <bits/stdc++.h>
using namespace std;

const int32_t inf32 = numeric_limits<int32_t>::max();

struct DSU {
    DSU(int n) : p(n, -1), time(n, inf32) {}

    int find(int x) { return p[x] < 0 ? x : find(p[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y, int t) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (p[x] > p[y]) swap(x, y);
        p[x] += p[y], p[y] = x;
        time[y] = t;
        return true;
    }
    int min_time(int x, int y) {
        int ret = 0;
        while (x != y) {
            if (time[x] > time[y]) swap(x, y);
            ret = max(ret, time[x]);
            x = p[x];
        }
        return ret;
    }

  private:
    vector<int> p, time;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, q, u, v;
    cin >> n >> m >> q;
    DSU dsu(n);
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        dsu.merge(--u, --v, i);
    }
    while (q--) {
        cin >> u >> v;
        cout << (dsu.same(--u, --v) ? dsu.min_time(u, v) : -1) << "\n";
    }
}

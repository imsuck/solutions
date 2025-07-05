#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
template<class T> using vec = vector<T>;

struct LCA {
    int n, m;
    vector<int> in, out, dep, st;

    LCA() {}
    template<class G>
    LCA(const G &g, int root = 0) :
        n(int(g.size())), m(2 * n), in(n), out(n), dep(n + 1), st(2 * m, n) {
        int t = 0;
        dep[n] = n;
        auto dfs = [&](auto &self, int v, int p) -> void {
            st[t + m] = v, in[v] = t++;
            for (int c : g[v]) {
                if (c == p) continue;
                dep[c] = dep[v] + 1;
                self(self, c, v);
            }
            st[t + m] = p, out[v] = t++;
        };
        dfs(dfs, root, n);
        for (int i = m; --i;) st[i] = argmin(st[i << 1], st[i << 1 | 1]);
    }

    int lca(int u, int v) const {
        if (in[u] > in[v]) swap(u, v);
        int ret = n;
        for (int l = in[u] + m, r = in[v] + m + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret = argmin(ret, st[l++]);
            if (r & 1) ret = argmin(st[--r], ret);
        }
        return ret;
    }
    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

  private:
    int argmin(int a, int b) const { return dep[a] < dep[b] ? a : b; }
};

fn solve() {
    i32 n, q;
    cin >> n >> q;
    vec<basic_string<i32>> g(n);
    for (i32 i = 1, p; i < n; i++) {
        cin >> p;
        g[p - 1] += i;
    }
    LCA t(g);
    while (q--) {
        i32 u, v;
        cin >> u >> v;
        cout << t.lca(u - 1, v - 1) + 1 << "\n";
    }
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}

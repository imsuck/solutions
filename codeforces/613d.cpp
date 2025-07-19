#include <bits/stdc++.h>
using namespace std;

struct HLD {
    int n;
    vector<int> par, in, out, hs;

    template<class G>
    HLD(G &g, int root = 0) : n(g.size()), par(n), in(n), out(n), hs(n) {
        dfs_sz(g, root);
        dfs_hld(g, root);
        assert(time == n);
    }

    int lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        for (;; v = par[hs[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (hs[u] == hs[v]) return u;
        }
    }
    auto path(int v, int p, bool es = 0) const {
        assert(in[p] <= in[v] && out[v] <= out[p]);
        vector<pair<int, int>> res;
        for (; hs[v] != hs[p]; v = par[hs[v]])
            res.emplace_back(in[hs[v]], in[v] + 1);
        res.emplace_back(in[p] + es, in[v] + 1);
        return res;
    }
    pair<int, int> subtree(int v) const {
        assert(0 <= v && v < n);
        return {in[v], out[v]};
    }

  private:
    int time = 0;
    template<class G> int dfs_sz(G &g, int v, int p = -1) {
        par[v] = p;
        int sz = 1, mx = 0;
        for (int &c : g[v]) {
            if (c == p) continue;
            int s = dfs_sz(g, c, v);
            sz += s;
            if (g[v][0] == p || mx < s) mx = s, swap(g[v][0], c);
        }
        return sz;
    }
    template<class G> void dfs_hld(G &g, int v, int p = -1) {
        in[v] = time++;
        for (int c : g[v]) {
            if (c == p) continue;
            hs[c] = (c == g[v][0] ? hs[v] : c);
            dfs_hld(g, c, v);
        }
        out[v] = time;
    }
};

struct VirtualTree {
    int n;
    HLD &hld;
    vector<basic_string<int>> g;

    VirtualTree(HLD &_hld) : n(_hld.n), hld(_hld), g(n) {}

    template<class V> int build(V vs) {
        auto anc = [&](int p, int v) {
            return hld.in[p] <= hld.in[v] && hld.out[v] <= hld.out[p];
        };
        auto cmp = [&](int u, int v) { return hld.in[u] < hld.in[v]; };
        int k = vs.size();
        sort(begin(vs), end(vs), cmp);
        for (int i = 1; i < k; i++) vs.push_back(hld.lca(vs[i - 1], vs[i]));
        sort(begin(vs), end(vs), cmp);
        k = unique(begin(vs), end(vs)) - begin(vs);
        for (int i = 0; i < k; i++) g[vs[i]].clear();
        stack<int> st;
        st.push(vs[0]);
        for (int i = 1; i < k; i++) {
            while (!anc(st.top(), vs[i])) st.pop();
            g[st.top()] += vs[i];
            st.push(vs[i]);
        }
        return vs[0];
    }
    auto &operator[](int v) { return g[v]; }
};

struct dumb_set {
    int n, cur = 1;
    vector<int> a;
    dumb_set(int _n) : n(_n), a(n) {}
    void clear() { cur++; }
    void insert(int x) { a[x] = cur; }
    bool find(int x) { return a[x] == cur; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v, g[v] += u;
    }
    HLD hld(g);
    VirtualTree t(hld);
    dumb_set s(n);
    vector<char> dp(n);
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        vector<int> vs(k);
        bool ok = true;
        for (int &v : vs) {
            cin >> v, v--;
            for (int c : g[v]) ok &= !s.find(c);
            s.insert(v);
        }
        if (!ok) {
            cout << "-1\n";
            s.clear();
            continue;
        }
        int rt = t.build(vs);
        int ans = 0;
        auto dfs = [&](auto f, int v) -> void {
            int cnt = 0;
            dp[v] = s.find(v);
            for (int c : t[v]) {
                f(f, c);
                cnt += dp[c];
            }
            if (s.find(v)) {
                ans += cnt;
            } else {
                cnt > 1 ? ans++ : dp[v] = cnt;
            }
        };
        dfs(dfs, rt);
        cout << ans << "\n";
        s.clear();
    }
}

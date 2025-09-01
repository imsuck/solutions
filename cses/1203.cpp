#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

template<class G> vec<i32> dominator_tree(const G &g, i32 s) {
    const i32 n = (i32)g.size();

    vec<i32> sdom(n, -1), par(n, -1), vs;
    vec<basic_string<i32>> gt(n);
    vs.reserve(n);
    i32 time = 0;

    auto dfs = [&](auto &rec, i32 v) -> void {
        sdom[v] = time++;
        vs.push_back(v);
        for (i32 c : g[v]) {
            if (sdom[c] == -1) par[c] = v, rec(rec, c);
            gt[c] += v;
        }
    };
    dfs(dfs, s);

    vec<i32> dsu(n), val(n);
    for (i32 i = 0; i < n; i++) dsu[i] = val[i] = i;

    auto merge = [&](i32 p, i32 v) { dsu[v] = p; };
    auto find = [&](auto &rec, i32 v) -> i32 {
        if (v == dsu[v]) return v;
        i32 r = rec(rec, dsu[v]);
        if (sdom[val[v]] > sdom[val[dsu[v]]]) val[v] = val[dsu[v]];
        return dsu[v] = r;
    };
    auto eval = [&](i32 v) { return find(find, v), val[v]; };

    vec<i32> us(n);
    vec<basic_string<i32>> bucket(n);
    for (i32 i = time - 1; i > 0; i--) {
        i32 w = vs[i];
        for (i32 v : gt[w]) sdom[w] = min(sdom[w], sdom[eval(v)]);
        bucket[vs[sdom[w]]] += w;
        for (i32 u : bucket[par[w]]) us[u] = eval(u);
        bucket[par[w]].clear();
        merge(par[w], w);
    }

    vec<i32> idom(n, -1);
    idom[s] = sdom[s];
    for (i32 i = 1; i < time; i++) {
        i32 w = vs[i], u = us[w];
        idom[w] = (sdom[w] == sdom[u]) ? sdom[w] : idom[u];
    }
    for (i32 v : vs) idom[v] = vs[idom[v]];
    return idom;
}

const i64 inf = 1.1e18;
template<class T> using heap = priority_queue<T, vec<T>, greater<>>;
auto chmin = [](auto &a, auto &&b) { return a > b ? a = b, 1 : 0; };

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, m;
    cin >> n >> m;
    vec<vec<pair<i32, i32>>> g(n), gt(n);
    for (i32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w), gt[v].emplace_back(u, w);
    }
    array<vec<i64>, 2> d;
    d.fill(vec<i64>(n, inf));
    auto dijk = [&](i32 t, i32 s) {
        heap<tuple<i64, i32>> q;
        d[t][s] = 0, q.emplace(0, s);
        while (q.size()) {
            auto [dv, v] = q.top();
            q.pop();
            if (dv > d[t][v]) continue;
            for (auto [u, w] : (t ? gt : g)[v])
                if (chmin(d[t][u], dv + w)) q.emplace(d[t][u], u);
        }
    };
    dijk(0, 0), dijk(1, n - 1);
    vec<basic_string<i32>> g2(n);
    for (i32 v = 0; v < n; v++)
        for (auto [u, w] : g[v])
            if (d[0][v] + w + d[1][u] == d[0][n - 1]) g2[v] += u;
    auto dom = dominator_tree(g2, 0);
    vec<i32> doms;
    for (i32 v = n - 1;; v = dom[v]) {
        doms.push_back(v + 1);
        if (v == dom[v]) break;
    }
    sort(begin(doms), end(doms));
    cout << doms.size() << "\n";
    for (i32 i : doms) cout << i << " ";
    cout << "\n";
}

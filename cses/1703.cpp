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

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 n, m;
    cin >> n >> m;
    vec<basic_string<i32>> g(n);
    for (i32 i = 0, u, v; i < m; i++) cin >> u >> v, g[--u] += --v;
    auto dom = dominator_tree(g, 0);
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

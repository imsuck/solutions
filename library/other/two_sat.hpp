#pragma once

#include "../graph/scc.hpp"

struct TwoSAT {
    int n;
    vector<basic_string<int>> g;

    TwoSAT(int _n) : n(_n), g(2 * n) {}

    void add_if(int x, int y) { g[x] += y, g[neg(y)] += neg(x); }
    void add_or(int x, int y) { add_if(neg(x), y); }
    void add_nand(int x, int y) { add_if(x, neg(y)); }
    void set_true(int x) { add_if(x, neg(x)); }
    void set_false(int x) { add_if(neg(x), x); }

    vector<bool> run() {
        vector<bool> res(n);
        auto [scc, rep, gd] = condense(g);
        for (int i = 0; i < n; i++) {
            if (rep[i] == rep[neg(i)]) return {};
            res[i] = rep[i] > rep[neg(i)];
        }
        return res;
    }

    int neg(int x) { return x < n ? x + n : x - n; }
};

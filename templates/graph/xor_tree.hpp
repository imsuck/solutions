#include <vector>
using namespace std;

struct XorTree {
    XorTree(int _n) : n(_n), adj(n), deg(n) {}

    void add_edge(int u, int v) {
        adj[u] ^= v, adj[v] ^= u, deg[u]++, deg[v]++;
    }
    void set_root(int v) { deg[v] = -1; }

    template<class F1, class F2> void run(F1 &&apply_edge, F2 &&apply_vertex) {
        int cnt = n;
        for (int i = 0; i < n; i++) {
            int v = i;
            while (deg[v] == 1) {
                int p = adj[v];
                deg[v]--, deg[p]--, adj[p] ^= v;
                apply_vertex(v), cnt--, apply_edge(p, v);
                v = p;
            }
            if (deg[v] == 0 || cnt == 1) apply_vertex(v);
        }
    }

  private:
    int n;
    vector<int> adj, deg;
};

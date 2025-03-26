#include <memory>
#include <random>
#include <unordered_map>
using namespace std;

template<class> struct st_alloc {};

namespace _ETT {
    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        ptr p = 0, l = 0, r = 0;
        int val = 0, sum = 0;
        int sz = 1;
        uint64_t pr = gen_pr();

        node() {}
        node(int x) : val(x), sum(x) {}

        static uint64_t gen_pr() {
            static mt19937_64 mt(uint64_t(make_unique<char>().get()));
            return mt();
        }
    };
    int sz(ptr t) { return t ? t->sz : 0; }
    int _sm(ptr t) { return t ? t->sum : 0; }
    ptr pull(ptr t) {
        t->sz = sz(t->l) + 1 + sz(t->r);
        t->sum = _sm(t->l) + t->val + _sm(t->r);
        return t;
    }
    ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        if (l->pr < r->pr) {
            l->r = merge(l->r, r);
            l->r ? l->r->p = l : 0;
            return pull(l);
        } else {
            r->l = merge(l, r->l);
            r->l ? r->l->p = r : 0;
            return pull(r);
        }
    }
    pair<ptr, ptr> split(ptr t, int k) {
        if (k < 0 || sz(t) < k) return {};
        if (!t) return {0, 0};
        int w = sz(t->l);
        ptr a, b;
        if (k <= w) {
            tie(a, b) = split(t->l, k);
            t->l = b;
            t->l ? t->l->p = t : 0;
            a ? a->p = 0 : 0;
            return {a, pull(t)};
        } else {
            tie(a, b) = split(t->r, k - w - 1);
            t->r = a;
            t->r ? t->r->p = t : 0;
            b ? b->p = 0 : 0;
            return {pull(t), b};
        }
    }
    int ord(ptr t) {
        int o = sz(t->l);
        for (; t->p; t = t->p)
            if (t == t->p->r) o += sz(t->p->l) + 1;
        return o;
    }
    ptr root(ptr t) {
        while (t->p) t = t->p;
        return t;
    }

    struct ETT {
        ETT(int _n) : n(_n), edges(n) {
            for (int i = 0; i < n; i++) edges[i][i] = new node(1);
        }

        void add_vertex() {
            edges.emplace_back(), edges[n][n] = new node(1), n++;
        }
        void link(int u, int v) {
            if (same(u, v)) return;
            ptr a = reroot(u, u), b = reroot(v, v, 1);
            merge(merge(a, edge(u, v)), merge(b, edge(v, u)));
        }
        void cut(int u, int v) {
            if (!same(u, v)) return;
            ptr a, b;
            tie(a, b) = split(reroot(u, v), 1);
            tie(a, b) = split(b, ord(edge(v, u)));
            split(b, 1);
        }
        bool same(int u, int v) { return root(edge(u, u)) == root(edge(v, v)); }
        int sub_size(int v, int p = -1) {
            if (p != -1) cut(v, p);
            int ret = root(edge(v, v))->sum;
            if (p != -1) link(v, p);
            return ret;
        }

        int n;
        vector<unordered_map<int, ptr>> edges;
        ptr &edge(int u, int v) {
            auto it = edges[u].find(v);
            return it != edges[u].end() ? it->second : edges[u][v] = new node();
        }

        ptr reroot(int u, int v, bool rev = false) {
            auto &e = edge(u, v);
            ptr a, b;
            tie(a, b) = split(root(e), ord(e) + rev);
            merge(b, a);
            return root(e);
        }
    };
} // namespace _ETT
using _ETT::ETT;

#include <utility>
#include <vector>
using namespace std;

#include "../other/st_alloc.hpp"

#define l ch[0]
#define r ch[1]
template<class M> struct LCT {
    using T = typename M::T;

    struct node;
    using ptr = node *;
    struct node : st_alloc<node> {
        node(int i = -1) : id(i) {}
        static inline node nil{};
        ptr p = &nil, ch[2]{&nil, &nil};
        T val = M::id(), path = M::id();
        T heavy = M::id(), light = M::id();
        bool rev = 0;
        int id;

        T sum() { return M::op(heavy, light); }

        void pull() {
            path = M::op(M::op(l->path, val), r->path);
            heavy = M::op(M::op(l->sum(), val), r->sum());
        }
        void push() {
            if (exchange(rev, 0)) l->reverse(), r->reverse();
        }
        void reverse() { swap(l, r), path = M::flip(path), rev ^= 1; }
    };
    static inline ptr nil = &node::nil;
    bool dir(ptr t) { return t == t->p->r; }
    bool is_root(ptr t) {
        return t->p == nil || (t != t->p->l && t != t->p->r);
    }
    void attach(ptr p, bool d, ptr c) {
        if (c) c->p = p;
        p->ch[d] = c, p->pull();
    }
    void rot(ptr t) {
        bool d = dir(t);
        ptr p = t->p;
        t->p = p->p;
        if (!is_root(p)) attach(p->p, dir(p), t);
        attach(p, d, t->ch[!d]);
        attach(t, !d, p);
    }
    void splay(ptr t) {
        for (t->push(); !is_root(t); rot(t)) {
            ptr p = t->p;
            if (p->p != nil) p->p->push();
            p->push(), t->push();
            if (!is_root(p)) rot(dir(t) == dir(p) ? p : t);
        }
    }
    void expose(ptr t) {
        ptr cur = t, prv = nil;
        for (; cur != nil; cur = cur->p) {
            splay(cur);
            cur->light = M::op(cur->light, cur->r->sum());
            cur->light = M::op(cur->light, M::inv(prv->sum()));
            attach(cur, 1, exchange(prv, cur));
        }
        splay(t);
    }

    vector<ptr> vert;
    LCT(int n = 0) {
        for (int i = 0; i < n; i++) vert.push_back(new node(i));
    }

    void expose(int v) { expose(vert[v]); }
    void evert(int v) { expose(v), vert[v]->reverse(); }
    void link(int v, int p) {
        evert(v), expose(p);
        assert(vert[v]->p == nil);
        attach(vert[p], 1, vert[v]);
    }
    void cut(int v) {
        expose(v);
        assert(vert[v]->l != nil);
        attach(vert[v], 0, vert[v]->l->p = nil);
    }
    T get(int v) { return vert[v]->val; }
    void set(int v, const T &x) {
        expose(v), vert[v]->val = x, vert[v]->pull();
    }
    void add(int v, const T &x) {
        expose(v), vert[v]->val = M::op(vert[v]->val, x), vert[v]->pull();
    }
    int lca(int u, int v) {
        if (u == v) return u;
        expose(u), expose(v);
        if (vert[u]->p == nil) return -1;
        splay(vert[u]);
        return vert[u]->p != nil ? vert[u]->p->id : u;
    }
    T path_fold(int u, int v) {
        evert(u), expose(v);
        return vert[v]->path;
    }
    T subtree_fold(int v, int p) {
        evert(p), cut(v);
        T ret = vert[v]->sum();
        link(v, p);
        return ret;
    }
};
#undef l
#undef r

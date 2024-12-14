#include <random>
#include <utility>
using namespace std;

template<class> struct st_alloc;

template<class M> struct Treap {
    using T = typename M::T;

    Treap() {}
    static Treap merge(const Treap &l, const Treap &r) {
        return Treap(merge(l.root, r.root));
    }
    pair<Treap, Treap> split(int k) {
        assert(0 <= k && k < size());
        auto s = split(root, k);
        return {Treap(s.first), Treap(s.second)};
    }

    int size() const { return sz(root); }
    bool empty() const { return size() == 0; }

    T operator[](int p) {
        assert(0 <= p && p < size());
        auto [a, b, c] = split(root, p, p + 1);
        T ret = prd(b);
        root = merge(a, b, c);
        return ret;
    }
    T get(int p) { return (*this)[p]; }
    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        auto [a, b, c] = split(root, l, r);
        if (b) b->rev ^= true;
        root = merge(a, b, c);
    }
    T operator()(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        auto [a, b, c] = split(root, l, r);
        T ret = prd(b);
        root = merge(a, b, c);
        return ret;
    }
    T prod(int l, int r) { return (*this)(l, r); }
    T all_prod() const { return prd(root); }

    void push_front(const T &x) { root = merge(new node(x), root); }
    void push_back(const T &x) { root = merge(root, new node(x)); }
    void pop_front() { root = split(root, 1).second; }
    void pop_back() { root = split(root, size() - 1).first; }

  private:
    struct node;
    using node_ptr = node *;
    struct node : st_alloc<node> {
        node_ptr l = nullptr, r = nullptr;
        T val = M::id(), prod = M::id();
        uint64_t pr = rng();
        int sz = 1;
        bool rev = false;
        node() {}
        node(const T &x) : val(x), prod(x) {}
        static uint64_t rng() {
            static mt19937 mt(uint64_t(+[](){}));
            return mt();
        }
    };

    node_ptr root = nullptr;
    explicit Treap(node_ptr t) : root(t) {}

    static int sz(node_ptr t) { return t ? t->sz : 0; }
    static T prd(node_ptr t) { return t ? t->prod : M::id(); }
    static void push(node_ptr t) {
        if (t->rev) {
            swap(t->l, t->r);
            if (t->l) t->l->rev ^= true;
            if (t->r) t->r->rev ^= true;
            t->rev = false;
        }
    }
    static node_ptr pull(node_ptr t) {
        t->sz = sz(t->l) + 1 + sz(t->r);
        t->prod = M::op(M::op(prd(t->l), t->val), prd(t->r));
        return t;
    }
    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        if (l->pr < r->pr) {
            r->l = merge(l, r->l);
            return pull(r);
        } else {
            l->r = merge(l->r, r);
            return pull(l);
        }
    }
    static pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        int w = sz(t->l);
        if (k <= w) {
            auto s = split(t->l, k);
            t->l = s.second;
            return {s.first, pull(t)};
        } else {
            auto s = split(t->r, k - w - 1);
            t->r = s.first;
            return {pull(t), s.second};
        }
    }
    static node_ptr merge(node_ptr a, node_ptr b, node_ptr c) {
        return merge(merge(a, b), c);
    }
    static tuple<node_ptr, node_ptr, node_ptr> split(node_ptr t, int l, int r) {
        node_ptr a, b, c;
        tie(a, b) = split(t, l);
        tie(b, c) = split(b, r - l);
        return {a, b, c};
    }
};

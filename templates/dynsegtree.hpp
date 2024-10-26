#include <cassert>

template<class> struct st_alloc;

// clang-format off
template<class M, class I = int> struct DynSegTree {
    using T = typename M::T;
    DynSegTree() = default;
    DynSegTree(int _n) : n(_n), root(new Node()) {}

    void set(I p, const T &x) {
        assert(0 <= p && p < n);
        auto rec = [&](auto &self, node_ptr t, I l, I r) -> void {
            if (r - l == 1) return void(t->val = x);
            I m = (l + r) / 2;
            if (p < m) self(self, t->c(0), l, m);
            else self(self, t->c(1), m, r);
            t->val = M::op(val(t->l), val(t->r));
        };
        rec(rec, root, 0, n);
    }
    T operator[](I p) const {
        assert(0 <= p && p < n);
        auto rec = [&](auto &self, node_ptr t, I l, I r) -> T {
            if (!t) return M::id();
            if (r - l == 1) return t->val;
            I m = (l + r) / 2;
            return p < m ? self(self, t->l, l, m) : self(self, t->r, m, r);
        };
        return rec(rec, root, 0, n);
    }
    T get(I p) const { return (*this)[p]; }
    T operator()(I l, I r) const {
        assert(0 <= l && l <= r && r <= n);
        auto rec = [&](auto &self, node_ptr t, I tl, I tr) -> T {
            if (!t) return M::id();
            if (l <= tl && tr <= r) return t->val;
            I tm = (tl + tr) / 2;
            if (r <= tm) return self(self, t->l, tl, tm);
            if (tm <= l) return self(self, t->r, tm, tr);
            return M::op(self(self, t->l, tl, tm), self(self, t->r, tm, tr));
        };
        return rec(rec, root, 0, n);
    }
    T prod(I l, I r) const { return (*this)(l, r); }
    T all_prod() const { return root->val; }

  private:
    struct Node;
    using node_ptr = Node *;
    struct Node : st_alloc<Node> {
        T val = M::id();
        node_ptr l = nullptr, r = nullptr;
        Node() {}
        inline node_ptr c(bool z) {
            return !z ? l ? l : l = new Node() : r ? r : r = new Node();
        }
    };

    I n;
    node_ptr root;

    static inline T val(node_ptr t) { return t ? t->val : M::id(); }
};
// clang-format on

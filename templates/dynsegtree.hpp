#include <cassert>

template<class T> struct st_alloc;

// clang-format off
template<class I, class M, class S = typename M::S> struct DynSegTree {
    DynSegTree() = default;
    DynSegTree(I _n) : n(_n), root(new Node(0, n)) {}

    void set(I p, const S &x) {
        assert(0 <= p && p < n);
        auto d = [&](auto self, const auto &t) {
            if (t->leaf()) return void(t->val = x);
            I m = (t->l + t->r) / 2;
            if (p < m) self(self, t->c(0));
            else self(self, t->c(1));
            t->val = M::op(val(t->left), val(t->right));
        };
        d(d, root);
    }
    S get(I p) const {
        assert(0 <= p && p < n);
        auto d = [&](auto &&self, const node_ptr &t) {
            if (!t) return M::e;
            if (t->leaf()) return t->val;
            I m = (t->l + t->r) / 2;
            return p < m ? self(self, t->left) : self(self, t->right);
        };
        return d(d, root);
    }
    S prod_all() const { return root->val; }
    S prod(I l, I r) const {
        assert(0 <= l && l <= r && r <= n);
        auto d = [&](auto self, const node_ptr &t) {
            if (!t) return M::e;
            if (r <= t->l || t->r <= l) return M::e;
            if (l <= t->l && t->r <= r) return t->val;
            return M::op(self(self, t->left), self(self, t->right));
        };

        return d(d, root);
    }

  private:
    struct Node;
    using node_ptr = Node *;
    struct Node : st_alloc<Node> {
        I l, r;
        S val = M::e;
        node_ptr left = nullptr, right = nullptr;

        Node() = default;
        Node(int lb, int rb) : l(lb), r(rb) {}

        inline bool leaf() const { return l == r - 1; }
        node_ptr &c(bool z) {
            I m = (l + r) / 2;
            if (!z) return left ? left : left = new Node(l, m);
            else return right ? right : right = new Node(m, r);
        }
    };

    I n;
    node_ptr root = nullptr;

    static inline S val(const node_ptr &t) { return t ? t->val : M::e; }
};
// clang-format on

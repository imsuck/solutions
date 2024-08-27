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
            self(self, t->c(p >= t->m()));
            t->val = M::op(val(t->left), val(t->right));
        };
        d(d, root);
    }
    S operator[](I p) const {
        assert(0 <= p && p < n);
        auto d = [&](auto self, const node_ptr &t) {
            if (!t) return M::e;
            if (t->leaf()) return t->val;
            return p < t->m() ? self(self, t->left) : self(self, t->right);
        };
        return d(d, root);
    }
    S get(int p) const { return (*this)[p]; }
    S operator()(I l, I r) const {
        assert(0 <= l && l <= r && r <= n);
        auto d = [&](auto self, const node_ptr &t) {
            if (!t) return M::e;
            if (r <= t->l || t->r <= l) return M::e;
            if (l <= t->l && t->r <= r) return t->val;
            return M::op(self(self, t->left), self(self, t->right));
        };

        return d(d, root);
    }
    S prod(I l, I r) const { return (*this)(l, r); }
    S prod_all() const { return root->val; }

  private:
    struct Node;
    using node_ptr = Node *;
    struct Node : st_alloc<Node> {
        I l, r;
        S val = M::e;
        node_ptr left = nullptr, right = nullptr;

        Node() = default;
        Node(int lb, int rb) : l(lb), r(rb) {}

        inline bool leaf() const { return r - l == 1; }
        inline I m() const { return (l + r) / 2; }
        node_ptr &c(bool z) {
            if (!z) return left ? left : left = new Node(l, m());
            else return right ? right : right = new Node(m(), r);
        }
    };

    I n;
    node_ptr root = nullptr;

    static inline S val(const node_ptr &t) { return t ? t->val : M::e; }
};
// clang-format on

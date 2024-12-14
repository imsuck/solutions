#include <chrono>
#include <cstdint>
#include <optional>
#include <random>
using namespace std;

template<class> struct st_alloc;

// NOTE: The copy constructor only copies the pointer. Becareful when doing
// `ordered_set<> s2 = s1;`
namespace bst {
    template<class T> struct bst_node : st_alloc<T> {
        using ptr = T *;
        ptr left = nullptr, right = nullptr;
        int sz = 1;

        void pull() {
            sz = (left ? left->sz : 0) + 1 + (right ? right->sz : 0);
        }
    };
    template<class T> int size(const T &t) { return t ? t->sz : 0; }

    template<class T, class Cmp>
    struct treap_node : bst_node<treap_node<T, Cmp>> {
        using base = bst_node<treap_node<T, Cmp>>;
        using ptr = typename base::node_ptr;

        treap_node() {}
        treap_node(const T &v) : val(v) {}

        T val;
        uint64_t pr = rng();
        static inline Cmp cmp{};

        static uint64_t rng() {
            static mt19937_64 mt(
                chrono::steady_clock::now().time_since_epoch().count());
            return mt();
        }

        static ptr merge(const ptr &l, const ptr &r) {
            if (!l) return r;
            if (!r) return l;
            if (l->pr > r->pr) {
                l->right = merge(l->right, r), l->pull();
                return l;
            } else {
                r->left = merge(l, r->left), r->pull();
                return r;
            }
        }
        static pair<ptr, ptr> split(const ptr &t, const T &k,
                                              bool include) {
            if (!t) return {nullptr, nullptr};
            if (cmp(t->val, k) || (t->val == k && include)) {
                auto s = split(t->right, k, include);
                t->right = s.first, t->pull();
                return {t, s.second};
            } else {
                auto s = split(t->left, k, include);
                t->left = s.second, t->pull();
                return {s.first, t};
            }
        }
    };
} // namespace bst

template<class T, class Cmp = less<>> struct ordered_set {
    using treap_node = bst::treap_node<T, Cmp>;
    using treap_ptr = treap_node *;

    ordered_set() {}

    void insert(const T &x) {
        if (contains(x)) return;
        auto [a, b] = treap_node::split(root, x, false);
        root = treap_node::merge(treap_node::merge(a, new treap_node(x)), b);
    }
    void erase(const T &x) {
        if (!contains(x)) return;
        treap_ptr a, b, c;
        tie(a, b) = treap_node::split(root, x, false);
        tie(b, c) = treap_node::split(b, x, true);
        root = treap_node::merge(a, c);
    }
    optional<T> kth_order(int k) {
        if (empty() || size() < k) return nullopt;
        int pref = 0;
        for (auto cur = root; cur != nullptr;) {
            if (pref + bst::size(cur->left) + 1 == k) return cur->val;
            if (pref + bst::size(cur->left) + 1 > k) {
                cur = cur->left;
            } else {
                pref += bst::size(cur->left) + 1;
                cur = cur->right;
            }
        }
        return nullopt;
    }
    int order_of(const T &x, bool include = true) {
        int ord = 0;
        for (auto cur = root; cur != nullptr;) {
            if (cmp(cur->val, x) || (cur->val == x && include)) {
                ord += bst::size(cur->left) + 1;
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return ord;
    }
    optional<T> pre_upper_bound(const T &x) {
        if (contains(x)) return x;
        return kth_order(order_of(x));
    }
    optional<T> lower_bound(const T &x) {
        if (contains(x)) return x;
        return kth_order(order_of(x, false) + 1);
    }

    int size() const { return root ? root->sz : 0; }
    bool empty() const { return !root; }
    bool contains(const T &x) {
        for (auto cur = root; cur != nullptr;) {
            if (cur->val == x) return true;
            cur = cmp(x, cur->val) ? cur->left : cur->right;
        }
        return false;
    }

  private:
    treap_ptr root = nullptr;
    static inline Cmp cmp{};
};

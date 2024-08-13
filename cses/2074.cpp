#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

struct Treap {
    Treap() = default;

    void reverse(int l, int r) {
        node_ptr a, b, c;
        tie(a, b) = split(move(root), l);
        tie(b, c) = split(move(b), r - l);
        b->rev ^= true;
        root = merge(merge(move(a), move(b)), move(c));
    }
    i64 sum(int l, int r) {
        node_ptr a, b, c;
        tie(a, b) = split(move(root), l);
        tie(b, c) = split(move(b), r - l);
        i64 res = b->sum;
        root = merge(merge(move(a), move(b)), move(c));
        return res;
    }

    void push_back(int x) { root = merge(move(root), new_node(x)); }

  private:
    struct Node;
    using node_ptr = unique_ptr<Node>;
    template<class... Args> static node_ptr new_node(Args &&...args) {
        return make_unique<Node>(forward<Args>(args)...);
    }

    struct Node {
        node_ptr left = nullptr, right = nullptr;
        i64 val, sum;
        uint64_t pr;
        int sz = 0;
        bool rev = false;

        Node(i64 x) : val(x), sum(x), pr(rng()), sz(1) {}

        static uint64_t rng() {
            static mt19937_64 mt(uint64_t(make_unique<char>().get()));
            return mt();
        }
    };

    node_ptr root = nullptr;

    explicit Treap(node_ptr _root) : root(move(_root)) {}

    static int size(const node_ptr &t) { return t ? t->sz : 0; }
    static void update(const node_ptr &t) {
        t->sz = size(t->left) + 1 + size(t->right);
        t->sum = t->val;
        if (t->left) t->sum += t->left->sum;
        if (t->right) t->sum += t->right->sum;
    }
    static void push(const node_ptr &t) {
        if (t->rev) {
            swap(t->left, t->right);
            if (t->left) t->left->rev ^= true;
            if (t->right) t->right->rev ^= true;
            t->rev = false;
        }
    }
    static node_ptr merge(node_ptr (l), node_ptr r) {
        if (!l) return r;
        if (!r) return l;
        push(l), push(r);
        if (l->pr < r->pr) {
            r->left = merge(move(l), move(r->left));
            update(r);
            return r;
        } else {
            l->right = merge(move(l->right), move(r));
            update(l);
            return l;
        }
    }
    static pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        int w = size(t->left);
        if (k <= w) {
            auto s = split(move(t->left), k);
            t->left = move(s.second);
            update(t);
            return {move(s.first), move(t)};
        } else {
            auto s = split(move(t->right), k - w - 1);
            t->right = move(s.first);
            update(t);
            return {move(t), move(s.second)};
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    Treap tr;
    for (int i = 0, a; i < n; i++) cin >> a, tr.push_back(a);
    while (q--) {
        int qt, l, r;
        cin >> qt >> l >> r;
        l--;
        if (qt == 1) tr.reverse(l, r);
        else cout << tr.sum(l, r) << "\n";
    }
}

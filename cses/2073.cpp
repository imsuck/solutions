#include <bits/stdc++.h>
using namespace std;
 
struct Treap {
    Treap() = default;
 
    void reverse(int l, int r) {
        node_ptr a, b, c;
        tie(a, b) = split(root, l);
        tie(b, c) = split(b, r - l);
        b->rev ^= true;
        root = merge(merge(a, b), c);
    }
 
    char get(int p) {
        node_ptr a, b, c;
        tie(a, b) = split(root, p);
        tie(b, c) = split(b, 1);
        char res = b->c;
        root = merge(merge(a, b), c);
        return res;
    }
 
    void push_back(char c) { root = merge(root, new_node(c)); }
 
  private:
    struct Node;
    using node_ptr = Node*;
    static inline stack<Node> node_pool;
    template<class... Args>static node_ptr new_node(Args &&...args) {
        node_pool.push(Node(forward<Args>(args)...));
        return &node_pool.top();
    }
 
    struct Node {
        node_ptr left = nullptr, right = nullptr;
        char c = '$';
        uint64_t pr;
        int sz = 0;
        bool rev = false;
 
        Node(char _c) : c(_c), pr(rng()), sz(1) {}
 
        static uint64_t rng() {
            static mt19937_64 mt(uint64_t(make_unique<char>().get()));
            return mt();
        }
    };
 
    node_ptr root = nullptr;
 
    int size(const node_ptr &t) { return t ? t->sz : 0; }
    void update(const node_ptr &t) {
        t->sz = size(t->left) + 1 + size(t->right);
    }
    void push(const node_ptr &t) {
        if (t->rev) {
            swap(t->left, t->right);
            if (t->left) t->left->rev ^= true;
            if (t->right) t->right->rev ^= true;
            t->rev = false;
        }
    }
    node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        if (l->pr < r->pr) {
            r->left = merge(l, r->left);
            update(r);
            return r;
        } else {
            l->right = merge(l->right, r);
            update(l);
            return l;
        }
    }
    pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        int w = size(t->left);
        if (k <= w) {
            auto s = split(t->left, k);
            t->left = s.second;
            update(t);
            return {s.first, t};
        } else {
            auto s = split(t->right, k - w - 1);
            t->right = s.first;
            update(t);
            return {t, s.second};
        }
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    Treap tr;
    for (int i = 0; i < n; i++) tr.push_back(s[i]);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        tr.reverse(a, b);
    }
    for (int i = 0; i < n; i++) {
        cout << tr.get(i);
    }
    cout << "\n";
}

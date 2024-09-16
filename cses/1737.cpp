#include <bits/stdc++.h>
using namespace std;

#define todo() assert(false)

template<class M> struct PersistentSegTree {
    using T = typename M::T;

    PersistentSegTree(const vector<T> &v, int q) : n(int(v.size())) {
        if (q >= 0) nodes.reserve((n + q) * __lg(n + q));
        nodes.emplace_back();
        roots.push_back(0);
        auto build = [&](auto &&self, int id, int l, int r) {
            if (r - l == 1) return void(nodes[id].val = v[l]);
            int m = (l + r) / 2;
            nodes[id].l = new_node(), nodes[id].r = new_node();
            self(self, nodes[id].l, l, m);
            self(self, nodes[id].r, m, r);
            nodes[id].val = M::op(child(id, 0).val, child(id, 1).val);
        };
        build(build, roots[0], 0, n);
    }

    void set(int time, int p, const T &x) {
        auto rec = [&](auto &&self, int &id, int l, int r) {
            id = new_node(nodes[id]);
            if (r - l == 1) return void(nodes[id].val = x);
            int m = (l + r) / 2;
            if (p < m) self(self, nodes[id].l, l, m);
            else self(self, nodes[id].r, m, r);
            nodes[id].val = M::op(child(id, 0).val, child(id, 1).val);
        };
        rec(rec, roots[time], 0, n);
    }
    T operator()(int time, int l, int r) const {
        auto rec = [&](auto &&self, int id, int tl, int tr) {
            if (l <= tl && tr <= r) return nodes[id].val;
            int tm = (tl + tr) / 2;
            if (r <= tm) return self(self, nodes[id].l, tl, tm);
            if (tm <= l) return self(self, nodes[id].r, tm, tr);
            return M::op(self(self, nodes[id].l, tl, tm),
                         self(self, nodes[id].r, tm, tr));
        };
        return rec(rec, roots[time], 0, n);
    }
    void push_back_ver(int time) { roots.push_back(roots[time]); }

  private:
    struct Node {
        int l = -1, r = -1;
        T val = M::id();
    };
    template<class... Args> int new_node(Args &&...args) {
        nodes.emplace_back(forward<Args>(args)...);
        return nodes.size() - 1;
    }

    int n;
    vector<Node> nodes;
    vector<int> roots;

    const Node &child(int id, bool z) const {
        return nodes[z ? nodes[id].r : nodes[id].l];
    }
};

struct M {
    using T = int64_t;
    static T id() { return 0; }
    static T op(T l, T r) { return l + r; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int64_t> init(n);
    for (int i = 0; i < n; i++) cin >> init[i];

    PersistentSegTree<M> st(init, q);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, i, x;
            cin >> k >> i >> x;
            st.set(k - 1, i - 1, x);
        } else if (t == 2) {
            int k, l, r;
            cin >> k >> l >> r;
            cout << st(k - 1, l - 1, r) << "\n";
        } else {
            int k;
            cin >> k;
            st.push_back_ver(k - 1);
        }
    }
}

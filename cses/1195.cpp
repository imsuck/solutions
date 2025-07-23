#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;
template<class T> bool chmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<class T> using pqueue = priority_queue<T, vector<T>, greater<>>;
template<size_t N, class T> auto mk_arr(const T &x) {
    array<T, N> a;
    return a.fill(x), a;
}
template<class... T> auto pop(priority_queue<T...> &q) {
    auto tmp = q.top();
    return q.pop(), tmp;
}

template<class I> const I inf = numeric_limits<I>::max();

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w);
    }
    auto d = mk_arr<2>(vector<i64>(n, inf<i64>));
    pqueue<tuple<i64, int, int>> q;
    d[0][0] = 0, q.emplace(0, 0, 0);
    while (q.size()) {
        auto [dv, k, v] = pop(q);
        if (dv != d[k][v]) continue;
        for (auto [u, w] : g[v]) {
            if (k == 0) {
                if (chmin(d[0][u], d[0][v] + w)) q.emplace(d[0][u], 0, u);
                if (chmin(d[1][u], d[0][v] + w / 2)) q.emplace(d[1][u], 1, u);
            } else if (chmin(d[1][u], d[1][v] + w)) {
                q.emplace(d[1][u], 1, u);
            }
        }
    }
    cout << d[1].back() << "\n";
}

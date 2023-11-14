#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;

const i32 MAX = 1e5 + 69;
i32 parent[MAX], sz[MAX];

i32 find_set(i32 v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

pair<i32, i32> union_sets(i32 a, i32 b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return {0, 0};
    if (sz[a] < sz[b])
        swap(a, b);
    parent[b] = a, sz[a] += sz[b];
    return {1, sz[a]};
}

void solve() {
    i32 n, m, mx = 0;
    cin >> n >> m;
    for (i32 i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    while (m--) {
        i32 a, b;
        cin >> a >> b;
        auto e = union_sets(a, b);
        n -= e.first;
        mx = max(mx, e.second);
        cout << n << " " << mx << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

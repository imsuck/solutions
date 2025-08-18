#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

string ops[]{"FILL A", "FILL B", "EMPTY A", "EMPTY B", "MOVE A B", "MOVE B A"};

template<class T> using pqueue = priority_queue<T, vector<T>, greater<>>;

const i32 inf = 1 << 30;

void solve() {
    i32 a, b, x;
    cin >> a >> b >> x;
    if (x % gcd(a, b) != 0 || x > a) {
        cout << "-1\n";
        return;
    }
    vector d(a + 1, vector(b + 1, inf));
    vector op(a + 1, vector(b + 1, -1));
    vector tr(a + 1, vector(b + 1, pair(-1, -1)));

    auto good = [&](int i, int j) { return d[i][j] == inf; };
    pqueue<tuple<i32, i32, i32>> q;
    d[0][0] = 0, q.emplace(0, 0, 0);
    while (q.size()) {
        auto [dv, i, j] = q.top();
        q.pop();
        if (dv != d[i][j]) continue;
        if (i != a && good(a, j)) {
            d[a][j] = dv + (a - i);
            op[a][j] = 0;
            tr[a][j] = {i, j};
            q.emplace(d[a][j], a, j);
        }
        if (j != b && good(i, b)) {
            d[i][b] = dv + (b - j);
            op[i][b] = 1;
            tr[i][b] = {i, j};
            q.emplace(d[i][b], i, b);
        }
        if (i) {
            if (good(0, j)) {
                d[0][j] = dv + i;
                op[0][j] = 2;
                tr[0][j] = {i, j};
                q.emplace(d[0][j], 0, j);
            }
            i32 ni = max(0, i + j - b), nj = i + j - ni;
            if (good(ni, nj)) {
                d[ni][nj] = dv + (i - ni);
                op[ni][nj] = 4;
                tr[ni][nj] = {i, j};
                q.emplace(d[ni][nj], ni, nj);
            }
        }
        if (j) {
            if (good(i, 0)) {
                d[i][0] = dv + j;
                op[i][0] = 3;
                tr[i][0] = {i, j};
                q.emplace(d[i][0], i, 0);
            }
            i32 nj = max(0, i + j - a), ni = i + j - nj;
            if (good(ni, nj)) {
                d[ni][nj] = dv + (j - nj);
                op[ni][nj] = 5;
                tr[ni][nj] = {i, j};
                q.emplace(d[ni][nj], ni, nj);
            }
        }
    }
    vec<i32> path;
    auto it = min_element(begin(d[x]), end(d[x]));
    for (i32 i = x, j = i32(it - begin(d[x])); i != -1 && op[i][j] != -1;
         tie(i, j) = tr[i][j])
        path.push_back(op[i][j]);
    reverse(begin(path), end(path));
    cout << path.size() << " " << *it << "\n";
    for (i32 i : path) {
        cout << ops[i] << "\n";
    }
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

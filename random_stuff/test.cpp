/*
Problem Name: Nested Ranges Count
Problem Link: https://cses.fi/problemset/task/2169
Author: Sachin Srivastava (mrsac7)
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define F first
#define S second

map<int, int> mp;
const int N = 2e5 + 1;
int T[N + 1] = {0};
void update(int n, int x, int val) {
    for (; x <= n; x += x & -x)
        T[x] += val;
}
int query(int x) {
    int s = 0;
    for (; x > 0; x -= x & -x)
        s += T[x];
    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    set<int> b;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[i] = {x, y};
        b.insert(y);
    }
    int cnt = 0;
    for (auto i : b) {
        mp[i] = ++cnt;
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += query(mp[v[i].S]);
        update(cnt, mp[v[i].S], 1);
    }

    cout << ans << '\n';
}

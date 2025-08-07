#include <bits/stdc++.h>
using namespace std;

bool cmp(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << endl;
    string resp;
    cin >> resp;
    return resp == "YES";
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), buf(n);
    iota(begin(a), end(a), 0);
    stable_sort(begin(a), end(a), cmp);
    for (int i = 0; i < n; i++) buf[a[i]] = i + 1;
    swap(a, buf);
    cout << "!";
    for (int i : a) cout << " " << i;
    cout << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}

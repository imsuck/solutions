#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n, cnt = 0;
    cin >> n;
    int l[n + 1];
    fill(l, l + n + 1, 0);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        l[a]++;
    }
    for (int i = n; i >= 0; i--) {
        if (cnt < i) {
            cnt += l[i];
            if (i <= l[i] || cnt >= i) {
                cout << "-1\n";
                return;
            }
        }
    }
    if (cnt == n)
        cout << "-1\n";
    else
        cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

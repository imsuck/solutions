#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 69;

int n, a[MAX], l = 1, r = 2, k = 0, res = 0, curr_len = 1;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
}

void solve() {
    if (n == 1) {
        cout << "1\n";
        return;
    }

    while (r <= n) {
        if (a[r] == a[l]) {
            curr_len++;
        } else if (k == 0) {
            k = r;
            curr_len++;
        } else {
            curr_len = 1;
            l = k;
            r = k;
            k = 0;
        }
        r++;

        res = max(res, curr_len);
    }

    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    input();
    solve();

    return 0;
}

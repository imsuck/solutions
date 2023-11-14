#include <bits/stdc++.h>
using namespace std;

void sol() {
    int n, k;
    cin >> n >> k;
    int res = n;
    string s;
    cin >> s;
    for (int i = 0; i < n - 1; i++) {
        string t;
        cin >> t;
        res -= (t != s) ? 1 : 0;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
        sol();

    return 0;
}

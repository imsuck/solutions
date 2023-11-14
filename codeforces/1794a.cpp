#include <bits/stdc++.h>
using namespace std;

bool cmp_len(string a, string b) { return a.size() < b.size(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int temp = 2 * n - 2;
        string a[temp];
        for (int i = 0; i < temp; i++) {
            cin >> a[i];
        }
        sort(a, a + temp, cmp_len);
        string p = a[temp - 1], s = a[temp - 2];
        reverse(s.begin(), s.end());
        if (p == s) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}

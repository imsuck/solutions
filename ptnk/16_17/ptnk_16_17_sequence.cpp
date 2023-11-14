#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        string ans = "YES";
        cin >> n >> m;
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            for (long p = 2; p * p <= a; p++) {
                while (a % p == 0) {
                    cnt[p]++;
                    a /= p;
                }
            }
            if (a != 1)
                cnt[a]++;
        }
        for (int i = 0; i < m; i++) {
            int a;
            cin >> a;
            for (long p = 2; p * p <= a; p++) {
                while (a % p == 0) {
                    cnt[p]--;
                    a /= p;
                }
            }
            if (a != 1)
                cnt[a]--;
        }

        for (auto it = cnt.begin(); it != cnt.end(); it++) {
            if (it->second != 0) {
                ans = "NO";
                break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}

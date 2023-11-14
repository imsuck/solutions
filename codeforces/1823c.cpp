#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k = 0;
        unordered_map<int, int> prime_count;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            for (long long p = 2; p * p <= a; p++) {
                while (a % p == 0) {
                    prime_count[p]++;
                    a /= p;
                }
            }
            if (a != 1)
                prime_count[a]++;
        }
        int rem = 0;
        for (pair<int, int> p : prime_count) {
            k += p.second / 2;
            rem += p.second % 2;
        }
        k += rem / 3;
        cout << k << "\n";
    }

    return 0;
}

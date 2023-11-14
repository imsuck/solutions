#include <bits/stdc++.h>
using namespace std;

int n_choose_k(long long n, long long k) {
    if (n < k)
        return 0;
    long long res = 1;
    if (k < n - k)
        k = n - k;
    for (int i = k + 1; i <= n; i++)
        res *= i;
    for (int i = 1; i <= n - k; i++)
        res /= i;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    int res[105][105] = {{0}};

    for (int n = 2; n < 105; n++) {
        for (int negs = 0; negs <= n / 2; negs++) {
            res[n][negs] = n_choose_k(n - negs, 2) + n_choose_k(negs, 2);
        }
    }

    while (t--) {
        int n, k;
        bool answered = false;
        cin >> n >> k;
        for (int i = 0; i <= n / 2; i++) {
            if (res[n][i] == k) {
                cout << "YES\n";
                for (int j = 0; j < n - i; j++)
                    cout << "1 ";
                for (int j = 0; j < i; j++)
                    cout << "-1 ";
                cout << "\n";
                answered = true;
                break;
            }
        }
        if (!answered) {
            cout << "NO\n";
        }
    }

    return 0;
}

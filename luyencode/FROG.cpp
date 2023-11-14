#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    int b[k + 1], dp[n + 1];
    fill_n(dp, n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= k; i++)
        cin >> b[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            dp[i] += i >= b[j] ? dp[i - b[j]] : 0;

    cout << dp[n] << "\n";

    return 0;
}

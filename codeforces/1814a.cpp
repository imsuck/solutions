#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        long long n, k;
        cin >> n >> k;

        string res = "NO\n";

        if (n % 2 == 0)
            res = "YES\n";
        else if (n % 2 != 0 && k % 2 != 0)
            res = "YES\n";
        else if (n % 2 != 0 && k % 2 == 0)
            res = "NO\n";

        cout << res;
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        unsigned long long n;
        cin >> n;
        cout << n * n + 2 * n + 2 << "\n";
    }

    return 0;
}

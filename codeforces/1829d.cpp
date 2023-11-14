#include <bits/stdc++.h>
using namespace std;

bool possible(int n, int m) {
    if (n == m)
        return true;
    if (n % 3 != 0)
        return false;
    return possible(n / 3, m) || possible(2 * n / 3, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << ((possible(n, m)) ? "YES" : "NO") << "\n";
    }

    return 0;
}

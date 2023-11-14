// Didn't make it...
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        double n;
        cin >> n;
        unsigned long long x = (unsigned long long)(sqrt(n));
        if ((x - 1) * (x - 1) >= n)
            cout << x - 1 << "\n";
        else if ((x) * (x) >= n)
            cout << x << "\n";
        else if ((x + 1) * (x + 1) >= n)
            cout << x + 1 << "\n";
    }

    return 0;
}

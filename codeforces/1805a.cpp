#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        int xor_res = 0;

        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            xor_res ^= temp;
        }

        if (n % 2 == 0) {
            if (xor_res == 0) {
                cout << "0\n";
            } else {
                cout << "-1\n";
            }
        } else {
            cout << xor_res << "\n";
        }
    }

    return 0;
}

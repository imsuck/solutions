#include <bits/stdc++.h>
using namespace std;

void sieve(int n, int k) {
    int count = 0;
    bool a[n + 1];
    vector<int> idx;
    fill(a, a + n + 2, true);
    a[0] = false;
    a[1] = false;

    for (int i = 2; i <= n; i++) {
        if (a[i]) {
            count += 1;
            if (count == k) {
                cout << i << "\n";
                return;
            }
            for (int j = 1; j * i + i <= n; j++) {
                if (a[j * i + i]) {
                    count += 1;
                }
                if (count == k) {
                    cout << j * i + i << "\n";
                    return;
                }
                a[j * i + i] = false;
            }
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int n, k;

    while (cin >> n >> k) {
        sieve(n, k);
    }

    return 0;
}

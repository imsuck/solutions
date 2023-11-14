#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, s = 0;
    cin >> m >> n;

    for (int i = 0; i < m; i++) {
        int s1 = 0;
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            s1 += a;
        }
        if (i % 2 != 0) {
            s += s1;
        }
    }

    cout << s;

    return 0;
}

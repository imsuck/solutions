#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long n;
    int k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        int halfn = (n + 1) / 2;
        if (x > halfn) {
            x = n - x + 1;
        }
        if (y > halfn) {
            y = n - y + 1;
        }

        switch (min(x, y) % 3) {
        case 0:
            cout << "YELLOW\n";
            break;
        case 1:
            cout << "RED\n";
            break;
        case 2:
            cout << "BLUE\n";
            break;
        }
    }
}

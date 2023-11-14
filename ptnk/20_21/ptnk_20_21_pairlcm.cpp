#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unsigned long long n;
    cin >> n;

    unsigned long long mid = n / 2;
    if (n == 2) {
        cout << 1;
    } else if (n % 2 != 0) {
        cout << mid * (mid + 1);
    } else if (mid % 2 != 0) {
        cout << mid * mid - 4;
    } else if (mid % 2 == 0) {
        cout << mid * mid - 1;
    }
    cout << "\n";

    return 0;
}

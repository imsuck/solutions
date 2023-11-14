#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long n, f = 0;
    cin >> n;

    while (n > 0) {
        n /= 5;
        f += n;
    }

    cout << f;

    return 0;
}

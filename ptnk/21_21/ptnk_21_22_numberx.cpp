#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    cin >> a >> b;

    if (a < b)
        swap(a, b);
    if (a == b) // Edge case
        cout << a;
    else if (a % b == 0) // Edge case
        cout << a - b;
    else
        cout << a * b / __gcd(a, b) - a - b;

    cout << "\n";

    return 0;
}

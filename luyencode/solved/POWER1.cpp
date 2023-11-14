#include <bits/stdc++.h>
using namespace std;

const int M = 1000000000 + 7;

int mod_power(int a, int b, int m) {
    if (b == 0) {
        return 1;
    }

    unsigned long long half = mod_power(a, b / 2, m);

    if (b & 1) {
        return (half * half * a) % m;
    } else {
        return (half * half) % m;
    }
}

int main() {
    int a, n;
    cin >> a >> n;

    cout << mod_power(a, n, M);

    return 0;
}

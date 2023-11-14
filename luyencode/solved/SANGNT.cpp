#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long n;
    cin >> n;
    bool sieve[n + 1];
    fill(sieve, sieve + n, true);

    for (unsigned long long i = 2; i * i <= n; i++) {
        if (sieve[i] == true) {
            for (unsigned long long j = i * i; j <= n; j += i) {
                sieve[j] = false;
            }
        }
    }

    for (unsigned long long i = 2; i <= n; i++) {
        if (sieve[i]) {
            cout << i << " ";
        }
    }

    return 0;
}

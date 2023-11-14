// Note to self: if you see x^2 use long long

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

bool sieve[5000069];

long long count_occur(int n, int i) {
    long long p = i, res = 0;
    while (p <= n) {
        res += n / p;
        p *= i;
    }
    return res;
}

long long power(long long a, long long n) {
    long long res = 1;
    a %= MOD;
    while (n > 0) {
        if (n % 2 != 0)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        n /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long res = 1;
    cin >> n;
    fill(sieve, sieve + n / 2 + 8, true);

    for (long long i = 2; i * i * 2 <= n; i++)
        if (sieve[i])
            for (long long j = i * i; j * 2 <= n; j += i)
                sieve[j] = false;
    for (long long i = 2; i * 2 <= n; i++)
        if (sieve[i])
            res = (res * power(i, count_occur(n, i) / 2 * 2)) % MOD;

    cout << res << endl;

    return 0;
}

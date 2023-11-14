// Find the number of divisors of n!
#include <bits/stdc++.h>
using namespace std;

int min_prime[10000];

// Why didn't I just use O(sqrt(n)) factorization
void era() {
    fill(min_prime, min_prime + 10000, 0);
    for (int i = 2; i * i < 10000; i++) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
            for (int j = i * i; j < 10000; j += i) {
                if (min_prime[j] == 0) {
                    min_prime[j] = i;
                }
            }
        }
    }
}

vector<int> factorize(int n) {
    vector<int> res(110, 0);
    for (int i = 2; i <= n; i++) {
        int j = i;
        while (j != 1) {
            res[min_prime[j]]++;
            j /= min_prime[j];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    era();

    int n;
    unsigned long long res = 1;
    cin >> n;

    vector<int> f = factorize(n);
    for (int i = 0; i < f.size(); i++) {
        if (f[i] != 0) {
            res *= f[i] + 1;
        }
    }
    cout << res - 1 << "\n";

    return 0;
}

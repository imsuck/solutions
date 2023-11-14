#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

const int MOD = 1e9 + 7;
const int MAX = 1e6 + 69;

bool is_prime[MAX];
vector<int> primes;

void sieve(int lim) {
    fill(is_prime, is_prime + lim + 3, true);
    for (ll i = 2; i <= lim; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= lim; j += i)
                is_prime[j] = false;
            primes.push_back(i);
        }
    }
}

ll power(ll a, ll n, ll mod) {
    ll res = 1;
    a %= mod;
    while (n > 0) {
        if (n % 2 != 0)
            res = (res * a) % mod;
        n /= 2;
        a = (a * a) % mod;
    }
    return res;
}

ll max_occur(ll p, ll lim) {
    ll res = 0, i = p;
    while (i <= lim) {
        res++;
        i *= p;
    }
    return res;
}

void solve() {
    int n;
    ll res = 1;
    cin >> n;
    sieve(n);
    for (int i = 0; i < primes.size(); i++)
        res = (res * power(primes[i], max_occur(primes[i], n), MOD)) % MOD;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}

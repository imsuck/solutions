#include <bits/stdc++.h>
using namespace std;

using i32 = int;

const i32 MAX = 1e6 + 69;

i32 min_p[MAX];

void sieve() {
    fill_n(min_p, MAX, 0);
    for (i32 i = 2; i * i < MAX; i++)
        if (min_p[i] == 0)
            for (i32 j = i; j < MAX; j += i)
                min_p[j] = (min_p[j] == 0) * i + (min_p[j] != 0) * min_p[j];
    for (i32 i = 2; i < MAX; i++)
        min_p[i] = (min_p[i] == 0) * i + (min_p[i] != 0) * min_p[i];
}

void solve() {
    i32 n, res = 1;
    map<i32, i32> m;
    cin >> n;
    while (n != 1) {
        m[min_p[n]]++;
        n /= min_p[n];
    }
    for (auto it = m.begin(); it != m.end(); it++)
        res *= it->second + 1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

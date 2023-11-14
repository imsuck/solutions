#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")

#include <iostream>
using namespace std;

int n, x, d[100069], h[1069], s[1069];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;

    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        for (int j = x; j >= h[i]; j--)
            d[j] = max(d[j], d[j - h[i]] + s[i]);
    }

    cout << d[x] << "\n";
}

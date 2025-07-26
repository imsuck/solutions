#include <bits/stdc++.h>
using namespace std;

template<size_t N, class T> auto mk_arr(const T &x) {
    array<T, N> a;
    return a.fill(x), a;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    auto f = mk_arr<30>(vector(n, 0));
    for (int &i : f[0]) cin >> i, i--;
    for (int l = 0; l + 1 < 30; l++)
        for (int i = 0; i < n; i++) f[l + 1][i] = f[l][f[l][i]];
    while (q--) {
        int v, k;
        cin >> v >> k, v--;
        for (int l = 29; l >= 0; l--)
            if (k >> l & 1) v = f[l][v];
        cout << v + 1 << "\n";
    }
}

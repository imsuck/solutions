#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int L = __lg(N) + 1;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> h(n + 1, 1.1e9);
    array<vector<int>, L> r;
    r.fill(vector(n + 1, n));
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        r[0][i] = i + 1;
    }

    for (int i = n - 1; i >= 0; i--)
        while (h[r[0][i]] <= h[i]) r[0][i] = r[0][r[0][i]];

    for (int l = 0; l + 1 < L; l++)
        for (int i = 0; i < n; i++) r[l + 1][i] = r[l][r[l][i]];

    while (q--) {
        int a, b;
        cin >> a >> b, a--;
        int ans = 1;
        for (int l = L - 1; l >= 0; l--) {
            if (r[l][a] < b) {
                ans += 1 << l;
                a = r[l][a];
            }
        }
        cout << ans << "\n";
    }
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tt;
    cin >> tt;

    while (tt--) {
        int n, k;
        cin >> n >> k;
        vec<int> b(n), v(n);
        vec<array<int, 2>> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i][0];
            a[i][1] = i;
        }
        for (int i = 0; i < n; i++)
            cin >> b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++)
            v[a[i][1]] = b[i];
        for (int x : v)
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}

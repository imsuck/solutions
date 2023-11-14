#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cout << (((n % 2 == 0) ? 2 : 1) * i) << " ";
        cout << "\n";
    }

    return 0;
}

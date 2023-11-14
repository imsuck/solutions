#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, cnt = 0;
        cin >> n;
        int a[n];
        bool inc, all_same = true;

        for (int i = 0; i < n; i++)
            cin >> a[i];

        for (int i = 1; i < n; i++) {
            bool prev = all_same;
            all_same &= a[i - 1] == a[i];
            if (prev != all_same)
                inc = a[i - 1] < a[i];
            if (!all_same && a[i - 1] < a[i] && !inc) {
                inc = true;
                cnt++;
            } else if (!all_same && a[i - 1] > a[i] && inc) {
                inc = false;
                cnt++;
            }
        }
        if (!all_same)
            cnt++;

        cout << cnt + 1 << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    int a[n], mx = 1;
    for (int i = 0; i < n; i++)
        cin >> a[i], mx = max(mx, a[i]);
    int cnt[mx + 1] = {};
    for (int i = 0; i < n; i++)
        cnt[a[i]]++;
    for (int i = mx, c = 0; i > 0; i--, c = 0) {
        for (int j = i; j <= mx; j += i)
            c += cnt[j];
        if (c >= 2) {
            cout << i;
            return 0;
        }
    }
    cout << 1;
}

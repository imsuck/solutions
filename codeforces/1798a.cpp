#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string ans = "Yes\n";
        cin >> n;
        int a[n], b[n], max_a = 0, max_b = 0;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int an = a[n - 1];
        int bn = b[n - 1];
        int smol = min(an, bn);
        if (an > bn)
            swap(an, bn);
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > an)
                swap(a[i], b[i]);
        }
        for (int i = 0; i < n - 1; i++) {
            if (b[i] > bn || a[i] > an) {
                ans = "No\n";
                break;
            }
        }
        cout << ans;
    }

    return 0;
}

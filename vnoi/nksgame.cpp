#include <bits/stdc++.h>
using namespace std;

// TIL: Find closest element in array/vector :D
int bsearch(const vector<int> &a, int x) {
    int n = a.size();
    if (a[0] > x)
        return a[0];
    if (a[n - 1] < x)
        return a[n - 1];
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == x)
            return a[mid];
        if (a[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (abs(a[l] - x) > abs(a[r] - x))
        return a[r];
    return a[l];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, res = INT_MAX;
    cin >> n;
    vector<int> b(n), c(n);

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    if (n == 1) {
        cout << abs(b[0] + c[0]) << "\n";
    }

    for (int i = 0; i < n; i++) {
        int x = bsearch(b, -c[i]);
        res = min(res, abs(x + c[i]));
    }

    cout << res << "\n";

    return 0;
}

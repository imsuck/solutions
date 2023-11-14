#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;

long long t[MAX], max_left[MAX], min_left[MAX], max_right[MAX], min_right[MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long res = -1e15;
    cin >> n;
    max_left[0] = -1e15;
    min_left[0] = 1e15;
    max_right[n + 1] = -1e15;
    min_right[n + 1] = 1e15;

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        max_left[i] = max(max_left[i - 1], t[i]);
        min_left[i] = min(min_left[i - 1], t[i]);
    }

    for (int i = n; i >= 1; i--) {
        max_right[i] = max(max_right[i + 1], t[i]);
        min_right[i] = min(min_right[i + 1], t[i]);
    }

    for (int i = 2; i < n; i++)
        res = max({res, (max_left[i - 1] - t[i]) * (t[i] - min_right[i + 1]),
                   (min_left[i - 1] - t[i]) * (t[i] - max_right[i + 1])});

    cout << res << "\n";

    return 0;
}

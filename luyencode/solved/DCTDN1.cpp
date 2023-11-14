#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, max_val = 1;
    cin >> n;
    int a[n], max_len[n];
    fill(max_len, max_len + n, 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                max_len[i] = max(max_len[i], max_len[j] + 1);
            }
        }
        max_val = max(max_val, max_len[i]);
    }
    cout << max_val;
}

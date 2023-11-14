#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;

    int m;
    cin >> m;
    string ms;
    cin >> ms;

    for (int i = 0; i < m; i++) {
        if (ms[i] == '1') {
            // TODO: Add 1 to s[i] (0<=i<n)
            for (int j = 0; j < n; j++) {
                s[j]++;
                if (s[j] > '9')
                    s[j] = '0';
            }
        } else {
            // TODO: Bring s[n-1] to front
            char end = s[n - 1];
            s = end + s.substr(0, n - 1);
        }
    }

    cout << s << "\n";

    return 0;
}

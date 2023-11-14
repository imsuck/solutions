#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s = "";
        for (int i = 0; i < n; i++) {
            s += "()";
        }
        int p = 0, q = 0;
        for (int i = 0; i < n; i++) {
            cout << s << "\n";
            while (p < 2 * n && s[p] != ')') {
                p++;
            }
            q = p;
            while (q < 2 * n && s[q] != '(') {
                q++;
            }
            swap(s[p], s[q]);
            p = q + 1;
        }
    }

    return 0;
}

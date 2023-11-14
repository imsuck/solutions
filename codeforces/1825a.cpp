#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define vec vector

void solve() {
    string s;
    cin >> s;
    if (s == string(s.size(), s[0]))
        cout << "-1\n";
    else
        cout << s.size() - 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}

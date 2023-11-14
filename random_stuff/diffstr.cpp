// Problem statement: Find min: `l` such that all substrings of length l of
// the string S is unique.
#include <bits/stdc++.h>
using namespace std;

int n, l = 1;
string s;

bool check(int l) {
    map<string, bool> m;
    string substr = s.substr(0, l);
    m[substr] = true;
    for (int i = 0; i + l < n; i++) {
        substr.erase(0, 1);
        substr += s[i + l];
        if (m[substr])
            return false;
        m[substr] = true;
    }
    return true;
}

int main() {
    freopen("diffstr.inp", "r", stdin);
    freopen("diffstr.out", "w", stdout);

    cin >> n;
    cin >> s;

    while (!check(l))
        l++;
    cout << l << "\n";

    return 0;
}

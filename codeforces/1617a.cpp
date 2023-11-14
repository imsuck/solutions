#include <bits/stdc++.h>
using namespace std;

void solve(string s, string t) {
    sort(s.begin(), s.end());
    if (t == "abc" && s[0] == 'a') {
        int occur[26];
        fill(occur, occur + 26, 0);
        for (int i = 0; i < s.size(); i++) {
            switch (s[i]) {
            case 'b':
                occur[2] += 1;
                break;
            case 'c':
                occur[1] += 1;
                break;
            default:
                occur[int(s[i]) - 97] += 1;
                break;
            }
        }
        string temp = "";
        for (int i; i < 26; i++) {
            switch (i) {
            case 1:
                temp += string(occur[i], 'c');
                break;
            case 2:
                temp += string(occur[i], 'b');
                break;
            default:
                temp += string(occur[i], char(i + 97));
                break;
            }
        }
        s = temp;
    }
    cout << s << "\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        string a, b;
        cin >> a >> b;
        solve(a, b);
    }

    return 0;
}

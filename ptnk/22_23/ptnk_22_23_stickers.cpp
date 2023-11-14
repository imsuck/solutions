#include <bits/stdc++.h>
using namespace std;

const int DIGITS = 10;
const int INF = 1e7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t[DIGITS], s[DIGITS];
    int res = INF;
    fill(t, t + DIGITS, 0);
    fill(s, s + DIGITS, 0);

    string ts, ss;
    cin >> ts >> ss;

    // Count occurences of each digit
    for (int i = 0; i < ts.size(); i++) {
        t[ts[i] - '0']++;
    }
    for (int i = 0; i < ss.size(); i++) {
        s[ss[i] - '0']++;
    }
    // 2 ~ 5; 6 ~ 9
    t[2] += t[5];
    t[6] += t[9];
    s[2] += s[5];
    s[6] += s[9];
    t[5] = 0;
    t[9] = 0;
    s[5] = 0;
    s[9] = 0;

    for (int i = 0; i < DIGITS; i++) {
        // Division by 0
        if (s[i] != 0) {
            res = min(res, t[i] / s[i]);
        }
    }

    cout << res << "\n";

    return 0;
}

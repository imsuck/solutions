#include <bits/stdc++.h>
using namespace std;

int main() {
    long cnt = 0;
    string s, ans = "";
    cin >> s;
    sort(s.begin(), s.end());
    ans += s + '\n';
    cnt++;
    while (next_permutation(s.begin(), s.end())) {
        ans += s + '\n';
        cnt++;
    }
    cout << cnt << '\n' << ans;
}

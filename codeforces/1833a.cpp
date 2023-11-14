#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        int n;
        cin >> n;
        str s;
        cin >> s;
        map<string, bool> m;
        for (int i = 0; i + 1 < n; i++)
            m[s.substr(i, 2)] = true;
        cout << m.size() << '\n';
    }

    return 0;
}

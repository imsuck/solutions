#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        str s;
        cin >> s;
        int a[500] = {0}, cnt = 0;
        for (int i = 0; i < s.size(); i++)
            a[s[i]]++;

        for (int i = 0; i < 500; i++)
            if (a[i] >= 2)
                cnt++;

        cout << (cnt > 1 ? "YES" : "NO") << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        map<char, int> m;
        string list;
        int max_occur = 0;
        cin >> list;
        if (list == string(4, list[0])) {
            cout << "-1\n";
            continue;
        }
        for (int j = 0; j < 4; j++) {
            m[list[j]] += 1;
            max_occur = max(max_occur, m[list[j]]);
        }
        if (m.size() == 2 && max_occur == 2 || m.size() == 3 || m.size() == 4) {
            cout << "4\n";
        } else if (m.size() == 2 && max_occur == 3) {
            cout << "6\n";
        }
    }

    return 0;
}

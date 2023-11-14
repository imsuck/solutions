#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int m;
        cin >> m;
        vector<vector<int>> a(m);
        vector<int> ans;
        string s = "";
        bool b[50005];
        fill(b, b + 50005, false);

        for (int i = 0; i < m; i++) {
            int n;
            cin >> n;
            for (int j = 0; j < n; j++) {
                int inp;
                cin >> inp;
                a[i].push_back(inp);
            }
        }

        for (int i = m - 1; i >= 0; i--) {
            int j = 0;
            while (j < a[i].size() && b[a[i][j]])
                j++;
            if (j < a[i].size())
                ans.push_back(a[i][j]);
            else
                ans.push_back(0);

            for (j = 0; j < a[i].size(); j++)
                b[a[i][j]] = true;
        }

        reverse(ans.begin(), ans.end());
        for (int i : ans) {
            if (i <= 0) { // just in case
                s = "-1";
                break;
            }
            s += to_string(i) + " ";
        }
        cout << s << "\n";
    }

    return 0;
}

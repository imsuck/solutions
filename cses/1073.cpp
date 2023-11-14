#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a;

    for (int i = 0; i < n; i++) {
        int inp;
        bool check = true;
        cin >> inp;
        int idx = upper_bound(a.begin(), a.end(), inp) - a.begin();
        if (idx >= a.size()) {
            a.push_back(inp);
        } else {
            a[idx] = inp;
        }
    }

    cout << a.size() << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, max_time = 0;
    unsigned long long res_id;
    cin >> n;

    vector<tuple<unsigned long long, int>> v(n);

    for (int i = 0; i < n; i++) {
        unsigned long long id;
        cin >> id;
        v[i] = make_tuple(id, i);
    }
    sort(v.begin(), v.end());

    if (n == 1 || n == 2 && get<0>(v[0]) != get<0>(v[1])) {
        cout << get<0>(v[0]) << "\n1\n" << flush;
        return 0;
    }

    int start = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            start = get<1>(v[i]);
        } // First element edge case
        else if (i == n - 1 && get<0>(v[i]) == get<0>(v[i - 1]) &&
                 max_time < get<1>(v[i]) - start + 1) {
            max_time = get<1>(v[i]) - start + 1;
            res_id = get<0>(v[i]);
        } // Last element edge case
        else if (0 < i && i < n - 1 && get<0>(v[i]) == get<0>(v[i + 1]) &&
                 get<0>(v[i]) != get<0>(v[i - 1])) {
            start = get<1>(v[i]);
        } // Start of i-th ID;
        else if (0 < i && i < n - 1 && get<0>(v[i]) != get<0>(v[i + 1]) &&
                 get<0>(v[i]) == get<0>(v[i - 1])) {
            if (max_time < get<1>(v[i]) - start + 1) {
                max_time = get<1>(v[i]) - start + 1;
                res_id = get<0>(v[i]);
            }
        } // End of i-th ID;
    }

    cout << res_id << "\n" << max_time << "\n";

    // Solution 2 (~Space complexity?~ can't return first person in list)
    // unordered_map<string, int> m;
    // string res_id;
    // int max_time = 0;

    // for (int i = 0; i < n; i++) {
    //     string id;
    //     cin >> id;

    //     if (!m[id]) {
    //         m[id] = i;
    //     } else if (max_time < i - m[id] + 1) {
    //         max_time = i - m[id] + 1;
    //         res_id = id;
    //     }
    // }

    // cout << res_id << "\n" << max_time << "\n";

    return 0;
}

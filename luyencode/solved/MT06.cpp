#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> list;

    for (int i = 0; i < m * n; i++) {
        int input;
        cin >> input;
        if (sqrt(input) == static_cast<int>(sqrt(input))) {
            if (find(list.begin(), list.end(), input) == list.end()) {
                list.push_back(input);
            }
        }
    }

    sort(list.begin(), list.end());

    if (list.empty()) {
        cout << "NOT FOUND";
        return 0;
    }

    for (int x : list) {
        cout << x << " ";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

vector<string> solve(int digit) {
    if (digit == 1)
        return vector<string>{"0", "1"};

    vector<string> sol, prev = solve(digit - 1);
    int size = prev.size();
    for (int i = 0; i < size; i++) {
        sol.push_back("0" + prev[i]);
    }
    for (int i = size - 1; i >= 0; i--) {
        sol.push_back("1" + prev[i]);
    }
    return sol;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (string s : solve(n)) {
        cout << s << "\n";
    }

    return 0;
}

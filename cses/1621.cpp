#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x;
    cin >> n;
    set<int> s;
    while (n--)
        cin >> x, s.insert(x);
    cout << s.size() << "\n";
}

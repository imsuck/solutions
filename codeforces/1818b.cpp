#include <bits/stdc++.h>
using namespace std;

void sol() {
    int n;
    cin >> n;
    if (n == 1)
        cout << "1";
    else if (n % 2 == 0)
        for (int i = 0; i < n; i++)
            if (i % 2 == 0)
                cout << i + 2 << " ";
            else
                cout << i << " ";
    else
        cout << "-1";

    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
        sol();

    return 0;
}

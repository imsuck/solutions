#include <bits/stdc++.h>
using namespace std;

#define mt(a, b) make_tuple(a, b)

long long get_value(long long x, long long y, long long n) {
    bool changed = false;
    long long diag = x + y - 1;
    long long val = 0;
    if (x + y >= n + 2) {
        val = -(n * n + 1);
        x = n - x + 1;
        y = n - y + 1;
        changed = true;
        diag = x + y - 1;
    }
    if (diag % 2 != 0) {
        val += (diag - 1) * diag / 2 + x;
    } else {
        val += (diag - 1) * diag / 2 + diag - x + 1;
    }
    if (changed)
        val *= -1;
    return val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, res;
    long long x, y;
    cin >> n >> x >> y;
    // TODO: Find a way to efficiently store visited squares
    // Might not be optimal
    // Actually good enough lol
    map<tuple<long long, long long>, bool> visited;

    string s;
    cin >> s;

    for (long long i = 0; i < s.size(); i++) {
        if (!visited[mt(x, y)]) {
            res += get_value(x, y, n);
            visited[mt(x, y)] = true;
        }

        if (s[i] == 'N')
            y--;
        else if (s[i] == 'E')
            x++;
        else if (s[i] == 'S')
            y++;
        else if (s[i] == 'W')
            x--;
    }

    if (!visited[mt(x, y)])
        res += get_value(x, y, n);

    cout << res << "\n";

    return 0;
}

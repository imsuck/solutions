#include <bits/stdc++.h>
using namespace std;

struct Item {
    Item(int v = -1, int i = -1) : val(v), idx(i){};
    int val;
    //! Original index
    int idx;
};

bool cmp(Item &a, Item &b) { return a.val < b.val; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, mx = 0;
    cin >> n >> m >> s;
    Item a[n + 1], b[m + 1];

    for (int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].idx = i;
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i].val;
        b[i].idx = i;
    }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + m + 1, cmp);

    int i = 1, j = m;
    int best_i = 0, best_j = 0;
    while (i <= n && j >= 1) {
        int sum = a[i].val + b[j].val;
        if (sum < s) {
            if (sum > mx) {
                mx = sum;
                best_i = a[i].idx;
                best_j = b[j].idx;
            }
            i++;
        } else if (sum == s) {
            best_i = a[i].idx;
            best_j = b[j].idx;
            break;
        } else {
            j--;
        }
    }

    cout << best_i << " " << best_j << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, s1, s2, t1 = 0, t2 = 0;
        bool swapped = false;
        cin >> n >> s1 >> s2;
        vector<tuple<int, int>> r(n + 1);
        vector<tuple<int, int>> a, b;

        if (s1 > s2) {
            swap(s1, s2);
            swapped = true;
        }

        for (int i = 1; i <= n; i++) {
            int inp;
            cin >> inp;
            r[i] = make_tuple(inp, i);
            a.push_back(r[i]);
            t1 += s1 * inp;
        }
        sort(r.begin(), r.end());
        sort(a.begin(), a.end());

        for (int i = n - 1; i >= 0; i--) {
            int newt1 = t1 - get<0>(r[i]) * s1;
            int newt2 = t2 + get<0>(r[i]) * s2;
            if (newt2 < newt1) {
                b.push_back(a[i]);
                a.pop_back();
                t1 = newt1;
                t2 = newt2;
            }
        }
        reverse(b.begin(), b.end());

        if (swapped) {
            swap(a, b);
        }
        cout << a.size() << " ";
        for (tuple<int, int> v : a) {
            cout << get<1>(v) << " ";
        }
        cout << "\n" << b.size() << " ";
        for (tuple<int, int> v : b) {
            cout << get<1>(v) << " ";
        }
        cout << "\n";
    }

    return 0;
}

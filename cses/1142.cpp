#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n + 2, -1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> left(n + 1), right(n + 1);
    stack<int> s;
    s.push(0);
    for (int i = 1; i <= n; i++) {
        while (s.size() && a[i] <= a[s.top()]) s.pop();
        left[i] = s.top() + 1, s.push(i);
    }
    s = {}, s.push(n + 1);
    for (int i = n; i >= 1; i--) {
        while (s.size() && a[i] <= a[s.top()]) s.pop();
        right[i] = s.top(), s.push(i);
    }
    int64_t mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, int64_t(right[i] - left[i]) * a[i]);
    }
    cout << mx << "\n";
}

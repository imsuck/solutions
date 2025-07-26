#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

const int N = (int)1e6 + 1;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> cnt(N);
    vector<i64> mult(N);
    for (int i = 0, a; i < n; i++) cin >> a, cnt[a]++;
    for (int i = 1; i < N; i++)
        for (int j = i; j < N; j += i) mult[i] += cnt[j];
    for (int i = 1; i < N; i++) mult[i] = mult[i] * (mult[i] - 1) / 2;
    for (int i = N - 1; i > 0; i--)
        for (int j = 2 * i; j < N; j += i) mult[i] -= mult[j];
    cout << mult[1] << "\n";
}

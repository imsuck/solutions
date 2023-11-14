#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
template <class T> using vec = vector<T>;
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

const int MAX = 1e6 + 69;

bool ans[MAX] = {false};

void preprocess() {
    for (i64 i = 2; i * i < MAX; i++) {
        i64 s = 1 + i, k = i * i;
        while (s < MAX) {
            s += k;
            k *= i;
            if (s < MAX) {
                ans[s] = true;
            }
        }
    }
}

void solve() {
    i32 n;
    cin >> n;
    cout << (ans[n] ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    preprocess();
    i32 t;
    cin >> t;
    while (t--)
        solve();
}

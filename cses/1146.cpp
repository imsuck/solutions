#include <bits/stdc++.h>
using namespace std;

int main() {
    int64_t n, ans = 0;
    cin >> n;
    
    for (int64_t m = 1; m < (1l << 51); m *= 2) {
        int64_t d = m * 2;
        ans += n / d * m;
        int64_t pos = n - n / d * d + 1;
        ans += max<int64_t>(pos - m, 0);
    }
    cout << ans << "\n";
}

// https://www.facebook.com/photo?fbid=800717918114187&set=pcb.3510685542542595
#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, prev_sum = 0, avg = 0;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> avg;
        cout << avg * i - prev_sum << " ";
        prev_sum += avg * i - prev_sum;
    }
}

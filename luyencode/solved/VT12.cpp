#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, min = INT32_MAX, max = INT32_MIN;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;
        min = std::min(min, input);
        max = std::max(max, input);
    }
    
    cout << max - min;
    
    return 0;
}
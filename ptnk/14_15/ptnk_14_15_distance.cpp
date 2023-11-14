#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int a[500] = {0}, b[500] = {0}, res = 0;
    for (int i = 0; i < s1.size(); i++)
        a[s1[i]]++;
    for (int i = 0; i < s2.size(); i++)
        b[s2[i]]++;
    for (int i = 'a'; i <= 'z'; i++)
        res += abs(a[i] - b[i]);
    cout << res << "\n";
}
// Solved with some assistance...
#include <bits/stdc++.h>
using namespace std;

bool mask[10];
vector<int> x(10);
map<int, bool> checked;
int c = 0;

int power(long long a, int n, int p) {
    long long res = 1;
    a %= p;
    while (n > 0) {
        if (n % 2 != 0)
            res = (res * a) % p;
        n = n >> 1;
        a = (a * a) % p;
    }
    return res;
}

int get_int() {
    int res = 0;
    for (int d : x) {
        res *= 10;
        res += d;
    }
    return res;
}

bool fermat(int n, int k) {
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    while (k--) {
        int a = 2 + rand() % (n - 4);
        if (__gcd(a, n) != 1 || power(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

void backtrack(vector<int> &nums, int i) {
    int curr = get_int();
    if (i != 0 && !checked[curr] && fermat(curr, 10))
        c++;
    checked[curr] = true;
    if (i == nums.size())
        return;

    for (int j = 0; j < nums.size(); j++) {
        if (mask[j]) {
            mask[j] = false;
            x.push_back(nums[j]);
            backtrack(nums, i + 1);
            x.pop_back();
            mask[j] = true;
        }
    }
}

void solve(string s) {
    vector<int> nums;
    for (int i = 0; i < s.size(); i++)
        if (i % 2 == 0)
            nums.push_back(s[i] - '0');

    backtrack(nums, 0);
    cout << c << "\n";
}

int main() {
    freopen("a.INP", "r", stdin);
    freopen("a.OUT", "w", stdout);

    int t;
    cin >> t;
    // Why u no sync
    string _temp;
    getline(cin, _temp);

    while (t--) {
        fill(mask, mask + 10, true);
        c = 0;
        string line;
        getline(cin, line);
        solve(line);
    }

    return 0;
}

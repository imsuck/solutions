// https://www.facebook.com/photo?fbid=800717951447517&set=pcb.3510685542542595
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, k, a, max = INT_MIN;
    cin >> n >> k;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        cin >> a;
        q.push(a);
        if (q.size() == k+1) {
            q.pop();
        }
    }
}

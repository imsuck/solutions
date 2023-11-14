#include <bits/stdc++.h>
using namespace std;

#define mp make_pair

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    stack<pair<int, int>> st;
    st.push(mp(0, 0));

    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        while (st.top().second >= a)
            st.pop();
        cout << st.top().first << " ";
        st.push(mp(i, a));
    }

    cout << "\n";

    return 0;
}

#import <bits/stdc++.h>
#define S std::

main() {
    int x, n;
    S cin >> x >> n;
    for (S multiset<int> s{0, x}, d = s; S cin >> x;
         S cout << *--end(d) << "\n") {
        auto i = s.insert(x);
        n = *++i, d.erase(d.find(n - *-- --i)), d.insert({n - x, x - *i});
    }
}

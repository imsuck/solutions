#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
const i32 MAX = 1e6 + 69;

i32 parent[MAX], size[MAX];

void make_set(i32 v) {
    parent[v] = v;
    size[v] = 1;
}

i32 find_set(i32 v) {
    if (parent[v] == v)
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(i32 a, i32 b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int main() {
    for (i32 i = 1; i < MAX; i++)
        make_set(i);
    union_sets(2, 3);
    union_sets(1, 3);
    union_sets(5, 6);
    union_sets(5, 7);
    union_sets(7, 10);
    union_sets(6, 2);
    cout << find_set(1) << "\n";
    for (i32 i = 1; i <= 10; i++)
        cout << i << "->" << parent[i] << "\n";
    cout << "\n";
    for (i32 i = 1; i <= 10; i++)
        cout << i << ": " << find_set(i) << "\n";
}

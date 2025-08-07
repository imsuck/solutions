#include <bits/stdc++.h>

namespace idk {const int N_MAX = 200'000;}

struct Node {
    int val;
    int rev;
    int size;
    int l, r;
} node[idk::N_MAX];

void maintain(int x) {
    node[x].size = node[node[x].l].size + 1 + node[node[x].r].size;
}

void pushdown(int x) {
    if (node[x].rev) {
        std::swap(node[x].l, node[x].r);
        node[node[x].l].rev ^= 1;
        node[node[x].r].rev ^= 1;
        node[x].rev = 0;
    }
}

void reverse(int x) {
    if (x == 0) return;
    node[x].rev ^= 1;
}

void zig(int& x) {
    int l = node[x].l;
    node[x].l = node[l].r;
    maintain(x);
    node[l].r = x;
    x = l;
}

void zag(int& x) {
    int r = node[x].r;
    node[x].r = node[r].l;
    maintain(x);
    node[r].l = x;
    x = r;
}

void splay(int& x, int k) {
    pushdown(x);
    if (int &l = node[x].l, &r = node[x].r, size = node[l].size; k == size) {
        return;
    } else if (k < size) {
        pushdown(l);
        if (int &ll = node[l].l, &lr = node[l].r, size = node[ll].size;
            k == size) {
            zig(x);
        } else if (k < size) {
            splay(ll, k);
            zig(x);
            zig(x);
        } else {
            splay(lr, k - size - 1);
            zag(l);
            zig(x);
        }
    } else {
        pushdown(r);
        k -= size + 1;
        if (int &rl = node[r].l, &rr = node[r].r, size = node[rl].size;
            k == size) {
            zag(x);
        } else if (k < size) {
            splay(rl, k);
            zig(r);
            zag(x);
        } else {
            splay(rr, k - size - 1);
            zag(x);
            zag(x);
        }
    }
}

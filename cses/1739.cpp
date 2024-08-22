#include <bits/stdc++.h>
using namespace std;

struct SegTree2D {
    SegTree2D() = default;
    SegTree2D(int h, int w) {
        while (H < h) H <<= 1;
        while (W < w) W <<= 1;
        t.assign(4 * H * W, 0);
    }

    void init(int h, int w, int x) { t[id(h + H, w + W)] = x; }
    void build() {
        for (int w = W; w < 2 * W; w++) {
            for (int h = H - 1; h > 0; h--) {
                t[id(h, w)] = t[id(h << 1, w)] + t[id(h << 1 | 1, w)];
            }
        }
        for (int h = 0; h < 2 * H; h++) {
            for (int w = W - 1; w > 0; w--) {
                t[id(h, w)] = t[id(h, w << 1)] + t[id(h, w << 1 | 1)];
            }
        }
    }

    void set(int h, int w, int x) {
        h += H, w += W;
        t[id(h, w)] = x;
        for (int i = h >> 1; i; i >>= 1) {
            t[id(i, w)] = t[id(i << 1, w)] + t[id(i << 1 | 1, w)];
        }
        for (; h; h >>= 1) {
            for (int j = w >> 1; j; j >>= 1) {
                t[id(h, j)] = t[id(h, j << 1)] + t[id(h, j << 1 | 1)];
            }
        }
    }
    int get(int h, int w) const { return t[id(h + H, w + W)]; }
    int _inner_prod(int h, int w1, int w2) const {
        int s = 0;
        for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
            if (w1 & 1) s += t[id(h, w1++)];
            if (w2 & 1) s += t[id(h, --w2)];
        }
        return s;
    }
    int prod(int h1, int w1, int h2, int w2) const {
        if (h1 >= h2 || w1 >= w2) return 0;
        int s = 0;
        h1 += H, h2 += H, w1 += W, w2 += W;
        for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
            if (h1 & 1) s += _inner_prod(h1++, w1, w2);
            if (h2 & 1) s += _inner_prod(--h2, w1, w2);
        }
        return s;
    }

  private:
    int H = 1, W = 1;
    vector<int> t;
    inline int id(int h, int w) const { return h * 2 * W + w; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    SegTree2D st(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            st.init(i, j, c == '*');
        }
    }
    st.build();

    while (q--) {
        int t, x, y, x2, y2;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 1) {
            int cur = st.get(x, y);
            st.set(x, y, 1 - cur);
        } else {
            cin >> x2 >> y2;
            cout << st.prod(x, y, x2, y2) << "\n";
        }
    }
}

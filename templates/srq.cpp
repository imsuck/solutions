#include <vector>
using namespace std;

// clang-format off
template<class T, class Op> struct RangeQuery {
  public:
    RangeQuery(const vector<T> &v, Op _op, T e)
        : n(v.size()), lg(__lg(n - 1) + 1), d(v), mask(n),
          dat(lg, vector<T>(n, e)), op(_op) {
        build(0, n - 1, 0);
    }

    T query(int l, int r) {
        r--;
        if (l == r) return d[l];
        int bits = __builtin_ctz(mask[l] ^ mask[r]);
        return op(dat[bits][l], dat[bits][r]);
    }

  private:
    int n, lg;
    vector<T> d;
    vector<int> mask;
    vector<vector<T>> dat;
    Op op;
    void build(int l, int r, int lvl) {
        if (l == r) return;
        int m = (l + r) / 2;
        dat[lvl][m] = d[m];
        for (int i = m - 1; i >= l; i--)
            dat[lvl][i] = op(d[i], dat[lvl][i + 1]);
        dat[lvl][m + 1] = d[m + 1];
        for (int i = m + 2; i < r + 1; i++)
            dat[lvl][i] = op(dat[lvl][i - 1], d[i]);
        for (int i = m + 1; i < r + 1; i++) mask[i] ^= 1 << lvl;
        build(l, m, lvl + 1);
        build(m + 1, r, lvl + 1);
    }
};
template<class T, class Op> auto make_rq(const vector<T> &v, Op op, T e) {
    return RangeQuery<T, Op>{v, op, e};
}
// clang-format on

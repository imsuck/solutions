#include <bits/stdc++.h>
using namespace std;

using f80 = long double;
using cplx = complex<f80>;
template<class T> using vec = vector<T>;

const f80 PI = acosl(-1);

void fft(vec<cplx> &a) {
    int n = int(a.size());
    for (int m = n; m > 1; m >>= 1) {
        f80 ang = 2.0 * PI / m;
        cplx omega = polar(f80(1), ang);
        for (int s = 0; s < n / m; s++) {
            cplx w = 1;
            for (int i = 0; i < m / 2; i++) {
                auto l = a[s * m + i];
                auto r = a[s * m + i + m / 2];
                a[s * m + i] = l + r;
                a[s * m + i + m / 2] = (l - r) * w;
                w *= omega;
            }
        }
    }
}

void ifft(vec<cplx> &a) {
    int n = int(a.size());
    for (int m = 2; m <= n; m <<= 1) {
        f80 ang = -2.0 * PI / m;
        cplx omega = polar(f80(1), ang);
        for (int s = 0; s < n / m; s++) {
            cplx w = 1;
            for (int i = 0; i < m / 2; i++) {
                auto l = a[s * m + i];
                auto r = a[s * m + i + m / 2] * w;
                a[s * m + i] = l + r;
                a[s * m + i + m / 2] = l - r;
                w *= omega;
            }
        }
    }
    for (int i = 0; i < n; i++) a[i] /= n;
}

template<class T> vector<f80> convolve(const vec<T> &a, const vec<T> &b) {
    int l = int(a.size() + b.size() - 1);
    int m = 1;
    while (m < l) m <<= 1;
    vec<cplx> s(begin(a), end(a)), t(begin(b), end(b));
    s.resize(m), t.resize(m);
    fft(s), fft(t);
    for (int i = 0; i < m; i++) s[i] *= t[i];
    ifft(s);
    vector<f80> res(l);
    for (int i = 0; i < l; i++) res[i] = s[i].real();
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = m - 1; i >= 0; i--) cin >> b[i];
    vector<f80> c = convolve(a, b);
    for (int i = 0; i < n + m - 1; i++)
        cout << int(round(c[i])) << " \n"[i == n + m - 2];
}

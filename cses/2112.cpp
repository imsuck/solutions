#include <bits/stdc++.h>
using namespace std;
 
namespace fft {
    template<class T> const T pi = acos(T(-1));
    template<class T> void fft(vector<T> &a) {
        using real_type = typename T::value_type;
 
        int n = int(a.size()), s = 0;
        while (1 << s < n) s++;
        assert(1 << s == n);
 
        static vector<T> omega;
        while (omega.size() <= s) {
            auto ang = 2 * pi<real_type> / (1 << omega.size());
            omega.push_back(polar<real_type>(1, ang));
        }
 
        for (int i = s; i > 0; i--) {
            int m = 1 << i;
            for (int y = 0; y < n; y += m) {
                T w = 1;
                for (int x = 0; x < m / 2; x++) {
                    T l = a[y | x];
                    T r = a[y | x | m >> 1];
                    a[y | x] = l + r;
                    a[y | x | m >> 1] = (l - r) * w;
                    w *= omega[i];
                }
            }
        }
    }
    template<class T> void ifft(vector<T> &a) {
        using real_type = typename T::value_type;
 
        int n = int(a.size()), s = 0;
        while (1 << s < n) s++;
        assert(1 << s == n);
 
        static vector<T> omega;
        while (omega.size() <= s) {
            auto ang = -2 * pi<real_type> / (1 << omega.size());
            omega.push_back(polar<real_type>(1, ang));
        }
 
        for (int i = 1; i <= s; i++) {
            int m = 1 << i;
            for (int y = 0; y < n; y += m) {
                T w = 1;
                for (int x = 0; x < m / 2; x++) {
                    T l = a[y | x];
                    T r = a[y | x | m >> 1] * w;
                    a[y | x] = l + r;
                    a[y | x | m >> 1] = l - r;
                    w *= omega[i];
                }
            }
        }
 
        for (int i = 0; i < n; i++) a[i] /= n;
    }
 
    template<class T = double, class U>
    vector<U> convolve(const vector<U> &a, const vector<U> &b) {
        int l = int(a.size() + b.size()) - 1;
        vector<complex<T>> na(begin(a), end(a)), nb(begin(b), end(b));
        int n = 1;
        while (n < l) n <<= 1;
        na.resize(n), nb.resize(n);
        fft(na), fft(nb);
        for (int i = 0; i < n; i++) na[i] *= nb[i];
        ifft(na);
        vector<U> res(l);
        for (int i = 0; i < l; i++) res[i] = U(round(na[i].real()));
        return res;
    }
};
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n = int(s.size());
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int val = s[i] == '1';
        a[i] = b[n - i - 1] = val;
    }
    auto c = fft::convolve(a, b);
    for (int i = n; i < c.size(); i++) cout << c[i] << " \n"[i == n - 1];
}

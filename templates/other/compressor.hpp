#include <limits>
#include <vector>
using namespace std;

template<class T = int> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    template<class... Ts> void push(Ts &...x) { (_push(x), ...); }
    void build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1, prv = numeric_limits<T>::max();
        for (auto &x : val) {
            if (prv != x) {
                id++, prv = x;
                og.push_back(x);
            }
            x.get() = id;
        }
    }
    int size() const { return int(og.size()); }
    T operator[](int i) const { return og[i]; }
    bool find(T x) const { return binary_search(begin(og), end(og), x); }

  private:
    void _push(T &x) { val.push_back(x); }
    void _push(pair<T, T> &p) {
        val.push_back(p.first), val.push_back(p.second);
    }
    template<class V> void _push(V &a) {
        for (auto &x : a) _push(x);
    }
};

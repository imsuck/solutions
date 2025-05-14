#include <vector>
using namespace std;

template<class T> struct Compressor {
    vector<reference_wrapper<T>> val;
    vector<T> og;

    void push(T &x) { val.push_back(x); }
    void build() {
        sort(begin(val), end(val));
        og.reserve(val.size());
        T id = -1, prv = -1;
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
};

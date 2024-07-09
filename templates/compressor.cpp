#include <vector>
using namespace std;

template<class T> struct Compressor {
  public:
    Compressor(const vector<T> &a) : v(a) {
        sort(begin(v), end(v));
        v.erase(unique(begin(v), end(v)), end(v));
    }
    bool find(T x) const { return binary_search(begin(v), end(v), x); }
    int operator()(T x) const {
        return int(lower_bound(begin(v), end(v)) - begin(v));
    }
    T operator[](int i) const { return v[i]; }
    int size() const { return (int)v.size(); }

  private:
    vector<T> v;
};

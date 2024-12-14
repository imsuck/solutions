#include <vector>
using namespace std;

template<class T> struct ptr32 {
    ptr32() {}
    ptr32(nullptr_t) : ptr32() {}
    template<class... Args> static ptr32 alloc(Args &&...args) {
        ptr32 p;
        if (del.size()) {
            p = del.back(), del.pop_back();
            *p = T(forward<Args>(args)...);
        } else {
            p.p = int(pool.size());
            pool.emplace_back(forward<Args>(args)...);
        }
        return p;
    }
    void dealloc(ptr32 p) { del.push_back(p); }

    operator bool() { return p; }
    bool operator==(const ptr32 &r) const { return p == r.p; }
    bool operator!=(const ptr32 &r) const { return p != r.p; }

    T &operator*() { return pool[p]; }
    T *operator->() { return &pool[p]; }

    static void reserve(int n) { pool.reserve(n + 1); }

  private:
    int p = 0;
    static inline vector<T> pool = vector<T>(1);
    static inline vector<ptr32> del;
};

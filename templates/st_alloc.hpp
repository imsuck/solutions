#include <stack>
using namespace std;

template<class T> struct st_alloc {
    static inline stack<T> pool;
    void *operator new(size_t) { return pool.push(T()), &pool.top(); }
    void operator delete(void *) {}
};

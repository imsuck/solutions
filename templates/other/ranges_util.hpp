template<class T> struct rev_t {
    T &cont;
    struct iterator {
        T cont;
        int p;
        bool operator!=(const iterator &r) const { return p != r.p; }
        void operator++() { p--; }
        typename T::value_type &operator*() { return cont[p]; }
    };
    iterator begin() { return {cont, int(cont.size()) - 1}; }
    iterator end() { return {cont, -1}; }
};
template<class T> struct crev_t {
    const T &cont;
    struct iterator {
        T cont;
        int p;
        bool operator!=(const iterator &r) const { return p != r.p; }
        void operator++() { p--; }
        const typename T::value_type &operator*() { return cont[p]; }
    };
    iterator begin() { return {cont, int(cont.size()) - 1}; }
    iterator end() { return {cont, -1}; }
};
template<class T> rev_t<T> rev(T &a) { return {a}; }
template<class T> crev_t<T> rev(const T &a) { return {a}; }
template<class T = int> struct range {
    range() {}
    range(T _stop) : stop(_stop) {}
    range(T _start, T _stop, T _step = 1)
        : start(_start), stop(_stop), step(_step) { assert(step != 0); }

    bool operator!=(range) { return step > 0 ? cur < stop : stop < cur; }
    void operator++() { cur += step; }
    T operator*() { return cur; }

    range begin() { return *this; }
    range end() { return {}; }

    T start = 0, stop, step = 1;
    T cur = start;
};

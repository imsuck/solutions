struct subsets {
    subsets(int m) : s(m), mask(m) {}

    using iterator = subsets;
    subsets begin() { return *this; }
    subsets end() { return {0}; }
    bool operator!=(subsets) { return s != -1; }
    void operator++() { s--; }
    int operator*() { return s &= mask; }

  private:
    int s, mask;
};

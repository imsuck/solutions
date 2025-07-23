#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <memory>
#include <random>
#include <set>

namespace libgen {
    struct pcg64 {
        using result_type = uint64_t;

        uint64_t state, inc;

        pcg64(uint64_t seed = get_entropy()) {
            state = seed * 0x9e3779b97f4a7c15 + 0x94d049bb133111eb;
            inc = state ^ state >> 34;
            inc |= 1, (*this)();
        }

        uint64_t operator()() {
            uint64_t x = state;
            state = x * 0x4afbfcc9230ed3f9 + inc;
            x ^= x >> ((x >> 59) + 5);
            x *= 0x4e42a2ff4fd72915;
            return x ^ x >> 43;
        }

        static constexpr uint64_t min() { return 0; }
        static constexpr uint64_t max() { return -1; }

      private:
        static uint64_t get_entropy() {
            return (uint64_t)std::make_unique<char>().get() ^
                   (uint64_t)std::chrono::steady_clock::now()
                       .time_since_epoch()
                       .count() ^
                   (uint64_t)std::random_device{}() ^
                   (uint64_t)__builtin_ia32_rdtsc();
        };
    };

    struct Gen {
        Gen(uint64_t seed = 0) {
            if (seed) pcg = {seed};
        }

        template<class T> T unif(T l, T r) {
            assert(l <= r);
            return T(l + next(r - l));
        }
        bool unif_bool() { return unif(0, 1) == 1; }
        double unif01() {
            uint64_t v = next(1ULL << 53);
            return double(v) / (1ULL << 53);
        }
        template<class T> std::pair<T, T> pair(T l, T r) {
            assert(r - l >= 1);
            T a, b;
            do {
                a = unif(l, r), b = unif(l, r);
            } while (a == b);
            if (a > b) std::swap(a, b);
            return {a, b};
        }
        template<class T, class C> void arr(C &a, T l, T r) {
            for (T &x : a) x = unif(l, r);
        }
        std::string str(size_t n, char l = 'a', char r = 'z') {
            std::string res(n, 0);
            arr(res, l, r);
            return res;
        }
        template<class T> void shuffle(T &x) { shuffle(begin(x), end(x)); }
        template<class It> void shuffle(It l, It r) {
            if (l == r) return;
            int i = 0, len = int(r - l);
            for (It it = l; it != r; i++, it++) {
                int j = unif(i, len - 1);
                if (j > i) iter_swap(it, l + j);
            }
        }
        template<class T> std::vector<T> perm(size_t n, T st = 0) {
            std::vector<T> p(n);
            std::iota(begin(p), end(p), st);
            shuffle(p);
            return p;
        }
        template<class T> std::vector<T> choice(size_t n, T l, T r) {
            assert(T(n) <= r - l + 1);
            std::set<T> res;
            while (res.size() < n) res.insert(uniform(l, r));
            return {res.begin(), res.end()};
        }
        std::vector<std::pair<int, int>> tree(size_t n, int id = 0) {
            std::vector<int> prufer(n - 2), deg(n, 1);
            arr(prufer, 0, (int)n - 1);
            for (int v : prufer) deg[v]++;
            std::vector<std::pair<int, int>> edges;
            edges.reserve(n - 1);
            for (int i = 0, j = 0; i < n; i++) {
                for (int v = i, p; v <= i && deg[v] == 1; v = p) {
                    if (j < n - 2) p = prufer[j++];
                    deg[v]--, deg[p]--;
                    if (v != p) edges.emplace_back(v + id, p + id);
                }
            }
            shuffle(edges);
            for (auto &[u, v] : edges)
                if (unif_bool()) std::swap(u, v);
            return edges;
        }
        std::vector<std::pair<int, int>>
        connected_graph(size_t n, size_t m, int id = 0) {
            assert(m + 1 >= n);
            auto graph = tree(n, id);
            std::set<std::pair<int, int>> s;
            for (auto [u, v] : graph) s.emplace(std::minmax(u, v));
            for (int i = (int)n - 1; i < m; i++) {
                std::pair<int, int> edge;
                do {
                    edge = pair(id, (int)n - 1 + id);
                } while (s.count(edge));
                s.emplace(edge);
                if (unif_bool()) std::swap(edge.first, edge.second);
                graph.emplace_back(edge);
            }
            shuffle(graph);
            return graph;
        }

      private:
        pcg64 pcg;

        uint64_t next(uint64_t upper) {
            if (!(upper & (upper + 1))) return pcg() & upper;
            int lg = 63 - __builtin_clzll(upper);
            uint64_t mask = (lg == 63) ? ~0ULL : (1ULL << (lg + 1)) - 1;
            while (true) {
                uint64_t r = pcg() & mask;
                if (r <= upper) return r;
            }
        }
    };
} // namespace libgen

using libgen::Gen;

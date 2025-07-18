#include <bits/stdc++.h>
using namespace std;

#include "libgen.hpp"

Gen gen;

void gen_test() {
    ofstream cout("a.inp");
    auto print = [&](auto &&...xs) { ((cout << xs << " "), ...); };
    [[maybe_unused]]
    auto println = [&](auto &&...xs) { print(xs...), cout << "\n"; };

    // const int n = gen.unif<int>(1, 1e8);
    // println(n);

    int n = 20;
    auto tree = gen.tree(n);
    for (auto [u, v] : tree) println(u, v);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Missing args\n";
        return 1;
    }

    const int seed = atoi(argv[1]);
    const int cnt = atoi(argv[2]);
    gen = Gen(seed);

    for (int i = 1; cnt == -1 || i <= cnt; i++) {
        gen_test();
        auto st = chrono::steady_clock::now();
        bool ng = system("./a.out <a.inp >a.output");
        auto dur = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - st
        );
        ng |= system("./safe.out <a.inp >a.ans");

        this_thread::sleep_for(20ms); // wait for files to finish writing
        if (ng || system("diff a.output a.ans") != 0) {
            cout << "Test " << i << ": NG " << (ng ? "(RTE)" : "(WA)") << endl;
            return 1;
        }
        cout << "Test " << i << ": OK, Time: " << dur.count() << "ms" << endl;
    }
    cout << "Maybe it is correct\n";
}

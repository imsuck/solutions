#include <bits/stdc++.h>
using namespace std;

mt19937 mt;
template<class T> T rand(T l, T r) {
    assert(l <= r);
    return uniform_int_distribution<T>{l, r}(mt);
}

void gen_test() {
    ofstream cout("a.inp");
    auto print = [&](auto &&...xs) { ((cout << xs << " "), ...); };
    [[maybe_unused]]
    auto println = [&](auto &&...xs) { print(xs...), cout << "\n"; };

    const int n = rand<int>(3, 3), q = rand<int>(1, 1);
    println(n, q);
    for (int i = 0; i < n; i++) cout << rand<int>(1, 2) << " \n"[i == n - 1];

    for (int _ = 0; _ < q; _++) {
        int l = rand<int>(1, n), r = rand<int>(1, n);
        if (l > r) swap(l, r);
        int x = rand<int>(-1, 1);
        println(l, r, x);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Missing args\n";
        return 1;
    }

    const int seed = atoi(argv[1]);
    const int cnt = atoi(argv[2]);
    mt = mt19937(seed);

    for (int i = 1; cnt == -1 || i <= cnt; i++) {
        gen_test();
        auto st = chrono::steady_clock::now();
        system("./a.out <a.inp >a.output");
        auto dur = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - st
        );
        system("./safe.out <a.inp >a.ans");

        this_thread::sleep_for(20ms); // wait for files to finish writing
        if (system("diff a.output a.ans") != 0) {
            cout << "Test " << i << ": NG" << endl;
            return 1;
        }
        cout << "Test " << i << ": OK, Time: " << dur.count() << "ms" << endl;
    }
    cout << "Maybe it is correct\n";
}

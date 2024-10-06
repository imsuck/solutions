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

    const int n = rand<int>(2, 100);
    println(n);
    for (int i = 0; i < n; i++) cout << rand<int>(1, 1000) << " \n"[i == n - 1];
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
        system("./a.out");
        system("./safe.out");

        this_thread::sleep_for(20ms); // wait for files to finish writing
        if (system("diff a.output a.ans") != 0) {
            cout << "Test " << i << ": NG" << endl;
            return 1;
        }
        cout << "Test " << i << ": OK" << endl;
    }
    cout << "Maybe it is correct\n";
}

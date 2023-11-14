#include <iostream>

int main() {
    long n, a = 0, i = 0, x[1001], y[1001];
    for (std::cin >> n; i < n; std::cin >> x[i] >> y[i++]);
    for (i = 0; i < n; a += x[i] * (y[++i % n] - y[(i - 2 + n) % n]));
    std::cout << llabs(a);
}

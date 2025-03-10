#include <random>
#include <algorithm>
#include <iterator>
#include <tuple>

int get_random_number(int n) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, n-1);

    return dis(gen);
}

std::tuple<int, int> get_random_pair(int n) {
    auto i = get_random_number(n);
    auto j = get_random_number(n - 1);
    if (j >= i) {
        ++j;
    }
    return {i, j};
}

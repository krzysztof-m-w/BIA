#include <iostream>
#include <vector>
#include "utils/random.h"
#include "utils/time_measure.h"

int main() {
    int a[] = {1, 2, 3, 4, 5};
    shuffle(a);
    for (int i = 0; i < 5; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    auto b = std::vector<int>{1, 2, 3, 4, 5};
    shuffle(b);
    for (int i = 0; i < 5; ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << '\n';
    auto time = time_measure(shuffle<std::vector<int>>, b);
    std::cout << "Time: " << time << '\n';
    return 0;
}
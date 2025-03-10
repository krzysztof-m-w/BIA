#ifndef RANDOM_H
#define RANDOM_H

int get_random_number(int n);

template<typename T>
void shuffle(T& container) {
    auto n = std::distance(std::begin(container), std::end(container));
    for (int i = n - 1; i > 0; --i) {
        auto j = get_random_number(i);
        std::iter_swap(std::begin(container) + i, std::begin(container) + j);
    }
}

template<std::size_t N>
void shuffle(int (&array)[N]) {
    for (std::size_t i = N - 1; i > 0; --i) {
        auto j = get_random_number(i);
        std::swap(array[i], array[j]);
    }
}

std::tuple<int, int> get_random_pair(int n);

#endif

#ifndef RANDOM_H
#define RANDOM_H

int get_random_number(int n);

template<typename T>
void shuffle(std::vector<T>& container) {
    auto n = static_cast<int>(container.size());
    for (int i = n - 1; i > 0; --i) {
        auto j = get_random_number(i);
        std::iter_swap(container.begin() + i, container.begin() + j);
    }
}

template<std::size_t N>
inline void shuffle(int (&array)[N]) {
    for (std::size_t i = N - 1; i > 0; --i) {
        auto j = get_random_number(i);
        std::swap(array[i], array[j]);
    }
}

inline void shuffle(int* array, int n){
    for (int i = n - 1; i > 0; --i) {
        auto j = get_random_number(i);
        std::swap(array[i], array[j]);
    }
}

std::tuple<int, int> get_random_pair(int n);

#endif

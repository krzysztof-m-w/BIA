#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <chrono>
#include <functional>

template<typename Func, typename... Args>
float time_measure(Func f, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    do{
        std::invoke(std::forward<Func>(f), std::forward<Args>(args)...);
    }while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1) || counter++ < 100);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count() / counter;
}

#endif

#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <chrono>
#include <functional>

typedef std::chrono::high_resolution_clock::time_point TimePoint;

inline TimePoint time_now(){
    return std::chrono::high_resolution_clock::now();
}

inline float time_diff(TimePoint start, TimePoint end){
    return std::chrono::duration<float>(end - start).count();
}

#endif

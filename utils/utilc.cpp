#include "utils.h"
#include <algorithm>

std::vector<int> argsort(const int* const values, int size) {
    std::vector<int> indices(size);
    
    for (size_t i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(),
              [&values](int i1, int i2) { return values[i1] < values[i2]; });

    return indices;
}
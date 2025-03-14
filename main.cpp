#include <iostream>
#include <vector>
#include "utils/random.h"
#include "utils/time_measure.h"
#include "utils/DataLoader.h"

int main() {
    DataLoader dl = DataLoader("qap/qapdatsol");
    for(int i = 0; i < dl.example_names.size(); i++){
        std::cout << i << std::endl;
        dl.load_problem_instance(i);
    }
    dl.load_problem_instance(68);
        


    return 0;
}
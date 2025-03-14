#include <iostream>
#include <vector>
#include "utils/random.h"
#include "utils/time_measure.h"
#include "utils/DataLoader.h"

int main() {
    DataLoader dl = DataLoader("qap/qapdatsol");
    dl.load_problem_instance(0);
    ProblemInstance pi = dl.problem_instances[0];
    std::cout << pi.compute_cost_quadratic(pi.optimal_solution) << std::endl;
    std::cout << pi.optimal_cost << std::endl;
    
    int* solution2 = new int[pi.n];;
    std::copy(pi.optimal_solution, pi.optimal_solution + pi.n, solution2);
    std::swap(solution2[0], solution2[1]);
    std::cout << pi.compute_cost_quadratic(solution2) << std::endl;
    std::cout << pi.compute_cost_delta(pi.optimal_solution, 0, 1, pi.optimal_cost) << std::endl;

    for(auto it = pi.get_neighborhood_iterator(); it != pi.get_neighborhood_end(); it++){
        std::cout << std::get<0>(*it) << " " << std::get<1>(*it) << std::endl;
    }
    return 0;
}
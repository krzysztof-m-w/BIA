#include <iostream>
#include <vector>
#include "utils/random.h"
#include "utils/time_measure.h"
#include "utils/DataLoader.h"

void test_data_correctness(std::vector<ProblemInstance> &problem_instances);

int main() {
    DataLoader dl = DataLoader("qap/qapdatsol");
    for(int i = 0; i < dl.example_names.size(); i++){
        dl.load_problem_instance(i);
    }
    test_data_correctness(dl.problem_instances);

    for(auto& pi : dl.problem_instances){
        int* solution = new int[pi.n];
        
        for(auto neighbor = pi.get_neighborhood_iterator(); neighbor != pi.get_neighborhood_end(); neighbor++){
            int i = std::get<0>(*neighbor);
            int j = std::get<1>(*neighbor);
            std::copy(pi.optimal_solution, pi.optimal_solution + pi.n, solution);
            std::swap(solution[i], solution[j]);
            int cost1 = pi.compute_cost_quadratic(solution);
            int delta = pi.compute_cost_delta(pi.optimal_solution, i, j, pi.optimal_cost);
            int cost2 = pi.optimal_cost + delta;
            if (cost1 != cost2){
                std::cout << "Error: " << cost1 << " != " << cost2 << " " << delta << std::endl;
                std::cout << "i: " << i << " j: " << j << std::endl;
                for(int k = 0; k < pi.n; k++){
                    std::cout << solution[k] << " ";
                }
                std::cout << std::endl;
                for(int k = 0; k < pi.n; k++){
                    std::cout << pi.optimal_solution[k] << " ";
                }
                std::cout << std::endl;
            }  
        }
        break; 
    }



    return 0;
}

void test_data_correctness(std::vector<ProblemInstance> &problem_instances){
    for(auto& pi : problem_instances){
        int* solution = new int[pi.n];
        std::copy(pi.optimal_solution, pi.optimal_solution + pi.n, solution);
        int optimal_cost = pi.compute_cost_quadratic(pi.optimal_solution);
        if(optimal_cost != pi.optimal_cost){
            std::cout << "Error: " << optimal_cost << " != " << pi.optimal_cost << std::endl;
            std::cout << "Name: " << pi.name << std::endl;
        }
    }
}
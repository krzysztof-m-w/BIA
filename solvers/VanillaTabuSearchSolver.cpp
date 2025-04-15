#include "VanillaTabuSearchSolver.h"
#include "../utils/utils.h"

VanillaTabuSearchSolver::VanillaTabuSearchSolver()
{
}

VanillaTabuSearchSolver::~VanillaTabuSearchSolver()
{
}


void VanillaTabuSearchSolver::solve(int *const solution_ptr)
{

    int* currentSolution = new int[this->problem_instance->n];
    this->problem_instance->get_random_solution(currentSolution);

    int current_cost = this->problem_instance->compute_cost_quadratic(currentSolution);

    int best_cost = current_cost;
    int* bestSolution = new int[this->problem_instance->n];
    std::copy(currentSolution, currentSolution + this->problem_instance->n, bestSolution);

    std::vector<std::vector<int>> tabuList(this->problem_instance->n, std::vector<int>(this->problem_instance->n, 0));

    int no_improvement_counter = 0;

    while(no_improvement_counter < this->max_no_improvement){
        int best_i, best_j;
        int best_moveCost = INT_MAX;
        for(auto neighborhood_it = this->problem_instance->get_neighborhood_iterator();
            neighborhood_it != this->problem_instance->get_neighborhood_end(); neighborhood_it++)
        {
            int i, j;
            std::tie(i, j) = *neighborhood_it;
            int moveCost = this->problem_instance->compute_cost_delta(currentSolution, i, j, 0);
            if(tabuList[i][j] > 0 && current_cost + moveCost > best_cost){
                continue;
            }
            if(moveCost < best_moveCost){
                best_i = i;
                best_j = j;
                best_moveCost = moveCost;
            }
        }
            current_cost += best_moveCost;
            this->problem_instance->apply_move_2opt(currentSolution, best_i, best_j);
            this->update_tabu_list(tabuList);
            tabuList[best_i][best_j] = this->tabu_tenure;
            this->iterations_counter++;
            this->step_counter++;
            no_improvement_counter++;
            if(current_cost < best_cost){
                best_cost = current_cost;
                std::copy(currentSolution, currentSolution + this->problem_instance->n, bestSolution);
                no_improvement_counter = 0;
            }        
    }

    std::copy(bestSolution, bestSolution + this->problem_instance->n, solution_ptr);
    delete[] currentSolution;
    delete[] bestSolution;
}

std::string VanillaTabuSearchSolver::get_name() const
{
    return "VanillaTabuSearchSolver";
}

#include "TabuSearchSolver.h"
#include "../utils/utils.h"

TabuSearchSolver::TabuSearchSolver()
{
}

TabuSearchSolver::~TabuSearchSolver()
{
}

std::vector<std::tuple<int,int>> TabuSearchSolver::get_candidate_list(int* const currentSolution, int candidateListSize)
{
    this->problem_instance->shuffle_neighborhood_2opt();
    auto neighborhood_iterator = this->problem_instance->get_neighborhood_iterator();
    int* candidateCosts = new int[candidateListSize];
    std::vector<std::tuple<int, int>> candidateList(candidateListSize);
    std::vector<int> candidateCostsOrder;

    for(int it = 0; it < candidateListSize; it++){
        int i, j;
        std::tie(i, j) = *(neighborhood_iterator+it);
        candidateCosts[it] = this->problem_instance->compute_cost_delta(currentSolution, i, j, 0);
        candidateList[it] = std::make_tuple(i, j);
    }
    candidateCostsOrder = argsort(candidateCosts, candidateListSize);

    std::vector<std::tuple<int, int>> orderedCandidateList;
    int limit = static_cast<int>(candidateListSize * 0.2);

    for (int it = 0; it < limit; it++) {
        orderedCandidateList.push_back(candidateList[candidateCostsOrder[it]]);
    }
    delete[] candidateCosts;
    return orderedCandidateList;
}

void TabuSearchSolver::update_tabu_list(std::vector<std::vector<int>>& tabuList){
    for(int i = 0; i < this->problem_instance->n; i++){
        for(int j = 0; j < this->problem_instance->n; j++){
            if(tabuList[i][j] > 0){
                tabuList[i][j]--;
            }
        }
    }
}

void TabuSearchSolver::solve(int *const solution_ptr)
{
    int candidateListSize = this->problem_instance->get_neighborhood_2opt_size() * 0.4;

    int* currentSolution = new int[this->problem_instance->n];
    this->problem_instance->get_random_solution(currentSolution);

    int current_cost = this->problem_instance->compute_cost_quadratic(currentSolution);

    int best_cost = current_cost;
    int* bestSolution = new int[this->problem_instance->n];
    std::copy(currentSolution, currentSolution + this->problem_instance->n, bestSolution);

    std::vector<std::vector<int>> tabuList(this->problem_instance->n, std::vector<int>(this->problem_instance->n, 0));

    int no_improvement_counter = 0;

    while(no_improvement_counter < this->max_no_improvement){
        std::vector<std::tuple<int, int>> candidateList = this->get_candidate_list(currentSolution, candidateListSize);
        int worstDelta = this->problem_instance->compute_cost_delta(currentSolution, std::get<0>(candidateList.back()), std::get<1>(candidateList.back()), 0);
        for(auto candidate_iterator = candidateList.begin(); candidate_iterator != candidateList.end(); candidate_iterator++){
            int i, j;
            std::tie(i, j) = *candidate_iterator;
            int moveCost = this->problem_instance->compute_cost_delta(currentSolution, i, j, 0);
            this->iterations_counter++;
            if(moveCost > worstDelta){
                break;
            }
            if(tabuList[i][j] > 0 && current_cost + moveCost > best_cost){
                continue;
            }
            current_cost += moveCost;
            this->problem_instance->apply_move_2opt(currentSolution, i, j);
            this->update_tabu_list(tabuList);
            tabuList[i][j] = this->tabu_tenure;
            this->step_counter++;
            no_improvement_counter++;
            if(current_cost < best_cost){
                best_cost = current_cost;
                std::copy(currentSolution, currentSolution + this->problem_instance->n, bestSolution);
                no_improvement_counter = 0;
            }        
        }
    }

    std::copy(bestSolution, bestSolution + this->problem_instance->n, solution_ptr);
    delete[] currentSolution;
    delete[] bestSolution;
}

std::string TabuSearchSolver::get_name() const
{
    return "TabuSearchSolver";
}

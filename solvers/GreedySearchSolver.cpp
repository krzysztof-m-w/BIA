#include "GreedySearchSolver.h"

GreedySearchSolver::GreedySearchSolver() : Solver() {
    this->ininitialSolution = NULL;
}

GreedySearchSolver::~GreedySearchSolver() {
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    Solver::~Solver();
}

void GreedySearchSolver::set_problem_instance(ProblemInstance* problem_instance) {
    Solver::set_problem_instance(problem_instance);
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    this->ininitialSolution = this->problem_instance->get_random_solution();
}

void GreedySearchSolver::reset(){
    Solver::reset();
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    this->ininitialSolution = this->problem_instance->get_random_solution();
}

void GreedySearchSolver::solve(int* const solution_ptr){
    int* currentSolution = this->ininitialSolution;
    int current_cost = this->problem_instance->compute_cost_quadratic(currentSolution);
    int moveCost;
    bool improvement = true;
    int i, j;

    while(true){
        improvement = false;

        for(auto neighborhood_it = this->problem_instance->get_neighborhood_iterator(); neighborhood_it != this->problem_instance->get_neighborhood_end(); neighborhood_it++){
            i = std::get<0>(*neighborhood_it);
            j = std::get<1>(*neighborhood_it);
            moveCost = this->problem_instance->compute_cost_delta(currentSolution, i, j, current_cost);
            if(moveCost < 0){
                this->problem_instance->apply_move_2opt(currentSolution, i, j);
                improvement = true;
                break;
            }
            this->iterations_counter++;
        }

        if(!improvement){
            break;
        }
    }

    std::copy(currentSolution, currentSolution + this->problem_instance->n, solution_ptr);
}
#include "SteepestSearchSolver.h"

SteepestSearchSolver::SteepestSearchSolver() : Solver() {
    this->ininitialSolution = NULL;
    this->step_counter = 0;
}

SteepestSearchSolver::~SteepestSearchSolver() {
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    Solver::~Solver();
}

void SteepestSearchSolver::set_problem_instance(ProblemInstance* problem_instance) {
    Solver::set_problem_instance(problem_instance);
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    this->ininitialSolution = new int[problem_instance->n];
    this->problem_instance->get_random_solution(this->ininitialSolution);
}

void SteepestSearchSolver::reset(){
    Solver::reset();
    if(this->ininitialSolution != NULL){
        delete[] this->ininitialSolution;
    }
    this->ininitialSolution = new int[problem_instance->n];
    this->problem_instance->get_random_solution(this->ininitialSolution);
    this->step_counter=0;
}

std::string SteepestSearchSolver::get_name() const {
    return "SteepestSearchSolver";
}

int SteepestSearchSolver::get_step_counter()
{
    return this->step_counter;
}

void SteepestSearchSolver::set_solve_info(const int *const solution)
{
    Solver::set_solve_info(solution);
    nlohmann::json* solutionData = &this->solution_info.back();
    solutionData->operator[]("initial_cost") = this->problem_instance->compute_cost_quadratic(this->ininitialSolution);
}

void SteepestSearchSolver::solve(int* const solution_ptr){
    int* currentSolution = new int[this->problem_instance->n];
    std::copy(this->ininitialSolution, this->ininitialSolution + this->problem_instance->n, currentSolution);
    int current_cost = this->problem_instance->compute_cost_quadratic(currentSolution);
    std::tuple<int, int> bestMove;
    int moveCost, bestMoveCost;
    bool improvement = true;
    int i, j;

    while(true){
        bestMoveCost = 0;
        improvement = false;

        for(auto neighborhood_it = this->problem_instance->get_neighborhood_iterator(); neighborhood_it != this->problem_instance->get_neighborhood_end(); neighborhood_it++){
            i = std::get<0>(*neighborhood_it);
            j = std::get<1>(*neighborhood_it);
            moveCost = this->problem_instance->compute_cost_delta(currentSolution, i, j, current_cost);
            if(moveCost < bestMoveCost){
                bestMoveCost = moveCost;
                bestMove = *neighborhood_it;
                improvement = true;
            }
            this->iterations_counter++;
        }

        if(improvement){
            i = std::get<0>(bestMove);
            j = std::get<1>(bestMove);
            current_cost += bestMoveCost;
            this->problem_instance->apply_move_2opt(currentSolution, i, j);
            this->step_counter++;
        }else{
            break;
        }

    }

    std::copy(currentSolution, currentSolution + this->problem_instance->n, solution_ptr);
    delete currentSolution;
}
    
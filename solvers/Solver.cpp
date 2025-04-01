#include "Solver.h"
#include "../utils/time_measure.h"
#include "../include/json.hpp"

Solver::Solver(){
    this->problem_instance = nullptr;
    this->iterations_counter = 0;
}

Solver::~Solver(){
}

void Solver::set_problem_instance(ProblemInstance* problem_instance){
    this->problem_instance = problem_instance;
}

int Solver::get_iterations_counter(){
    return this->iterations_counter;
}

void Solver::reset(){
    this->iterations_counter = 0;
}

std::string Solver::get_name() const {
    return "DefaultSolver"; // Replace with the appropriate name for the solver
}

void Solver::read_configuration(const std::string& file_path, const std::string& problem_name){
    std::cout << "No configuration needed for solver: " + this->get_name() << std::endl;
}

int Solver::get_step_counter(){
    return this->get_iterations_counter();
}

void Solver::set_solve_info(const int* const solution){
    nlohmann::json solutionData;
    solutionData["solution"] = std::vector<int>(solution, solution + this->problem_instance->n);
    solutionData["iteration_counts"] = this->get_iterations_counter();
    solutionData["step_count"] = this->get_step_counter();
    this->solution_info.push_back(solutionData);
}

void Solver::add_cost_to_solve_info(){
    for(auto& solutionData : this->solution_info){
        std::vector<int> solution = solutionData["solution"].get<std::vector<int>>();
        solutionData["cost"] = this->problem_instance->compute_cost_quadratic(solution.data());
    }
}

void Solver::add_time_to_solve_info(int start, int offset, float avg_time)
{
    auto solutionDataIterator = std::next(this->solution_info.begin(), start);
    for(int i=0; i<offset; i++){
        solutionDataIterator++;
        if (solutionDataIterator != this->solution_info.end() && solutionDataIterator->is_object()) {
            (*solutionDataIterator)["avg_time"] = avg_time;
        } else {
            return;
        }
    }
}

std::list<nlohmann::json> Solver::get_solution_info(){
    return this->solution_info;
}
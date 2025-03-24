#include "Solver.h"
#include "../utils/time_measure.h"

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

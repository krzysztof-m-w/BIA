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
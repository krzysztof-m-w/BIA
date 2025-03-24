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

float Solver::measure_solve_time(){
    return time_measure(&Solver::solve, this);
}

int Solver::get_iterations_counter(){
    return this->iterations_counter;
}

void Solver::reset_sovler(){
    this->iterations_counter = 0;
}
#include "RandomSearchSolver.h"
#include "../utils/random.h"
#include "../utils/time_measure.h"


RandomSearchSolver::RandomSearchSolver() : Solver() {
    this->max_time = 1.0;
}

int* RandomSearchSolver::solve() {
    int* best_solution = this->problem_instance->get_random_solution();
    int best_cost = this->problem_instance->compute_cost_quadratic(best_solution);

    int* current_solution = this->problem_instance->get_random_solution();
    int current_cost;

    TimePoint start_time = time_now();

    while (time_diff(start_time, time_now()) < this->max_time) {
        shuffle(current_solution, this->problem_instance->n);
        current_cost = this->problem_instance->compute_cost_quadratic(current_solution);

        if (current_cost < best_cost) {
            best_cost = current_cost;
            std::copy(current_solution, current_solution + this->problem_instance->n, best_solution);
        }

        this->iterations_counter++;
    }

    delete[] current_solution;

    return best_solution;
}


    
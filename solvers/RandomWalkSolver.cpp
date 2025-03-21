#include "RandomWalkSolver.h"
#include "../utils/time_measure.h"
#include "../utils/random.h"

RandomWalkSolver::RandomWalkSolver() : Solver(){
    this->max_time = 1.0;
}


void RandomWalkSolver::set_max_time(float max_time){
    this->max_time = max_time;
}

int* RandomWalkSolver::solve(){
    int* current_solution = this->problem_instance->get_random_solution();
    int current_cost = this->problem_instance->compute_cost_quadratic(current_solution);
    int n = this->problem_instance->n;

    int* best_solution = new int[this->problem_instance->n];
    std::copy(current_solution, current_solution + this->problem_instance->n, best_solution);
    int best_cost = current_cost;

    int random_i;
    std::tuple<int, int> random_neighbor;
    int i, j;
    int delta;

    TimePoint start_time = time_now();
    while(time_diff(start_time, time_now()) < this->max_time){
        random_i = get_random_number(this->problem_instance->get_neighborhood_2opt_size());
        random_neighbor = *(this->problem_instance->get_neighborhood_iterator() + random_i);
        i = std::get<0>(random_neighbor);
        j = std::get<1>(random_neighbor);

        delta = this->problem_instance->compute_cost_delta(current_solution, i, j, current_cost);
        current_cost += delta;

        std::swap(current_solution[i], current_solution[j]);

        if(current_cost < best_cost){
            std::copy(current_solution, current_solution + this->problem_instance->n, best_solution);
            best_cost = current_cost;
        }

        this->iterations_counter++;

    }
    return current_solution;
}
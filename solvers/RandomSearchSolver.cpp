#include "RandomSearchSolver.h"
#include "../utils/random.h"
#include "../utils/time_measure.h"
#include "../include/json.hpp"
#include "../utils/read_json.h"

#include <fstream>


RandomSearchSolver::RandomSearchSolver() : Solver() {
    this->max_time = 1.0;
    this->global_configuration = false;
}

void RandomSearchSolver::set_max_time(float max_time) {
    this->max_time = max_time;
}

std::string RandomSearchSolver::get_name() const{
    return "RandomSearchSolver";
}

void RandomSearchSolver::read_configuration(const std::string& file_path, const std::string& problem_name){
    if(this->global_configuration){
        std::cout << "Global configuration already set for solver: " + this->get_name() << std::endl;
        return;
    }
    nlohmann::json json;
    if(file_path != ""){
        std::cout << "Reading configuration from file: " + file_path << std::endl;
        json = read_json(file_path, {"max_time"});
        this->global_configuration = true;
    }else if(problem_name != ""){
        std::string file_path = "results/" + problem_name + "-GreedySearchSolver.json";
        std::cout << "Trying to read configuration from file: " + file_path << std::endl;
        json = read_json(file_path, {"avg_time"});
        this->max_time = json["avg_time"];
        return;
    }else{
        std::string default_file_path = "config/" + this->get_name() + ".json";
        std::cout << "Trying to read default configuration from: " + default_file_path << std::endl;
        json = read_json(default_file_path, {"max_time"});
    }
    this->max_time = json["max_time"];
}

void RandomSearchSolver::solve(int* const solution_ptr) {
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
    std::copy(best_solution, best_solution + this->problem_instance->n, solution_ptr);
    delete[] current_solution;
    delete[] best_solution;
}

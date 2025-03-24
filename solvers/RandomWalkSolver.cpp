#include "RandomWalkSolver.h"
#include "../utils/time_measure.h"
#include "../utils/random.h"
#include "../utils/read_json.h"

RandomWalkSolver::RandomWalkSolver() : Solver(){
    this->max_time = 1.0;
    this->global_configuration = false;
}


void RandomWalkSolver::set_max_time(float max_time){
    this->max_time = max_time;
}

std::string RandomWalkSolver::get_name() const {
    return "RandomWalkSolver";
}

void RandomWalkSolver::read_configuration(const std::string& file_path, const std::string& problem_name){
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

void RandomWalkSolver::solve(int* const solution_ptr){
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
    std::copy(best_solution, best_solution + this->problem_instance->n, solution_ptr);
    delete[] current_solution;
}
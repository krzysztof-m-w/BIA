#include "SimulatedAnnealingSolver.h"
#include "../utils/random.h"

void SimulatedAnnealingSolver::adjust_initial_temperature(int *best_solution, int best_cost)
{
    int* current_solution = new int[problem_instance->n];
    int current_cost = best_cost;
    std::copy(best_solution, best_solution + problem_instance->n, current_solution);
    const int step_window = 20;
    int accepted_count = 0;
    int rejected_count = 0;
    int index = 0;
    int step_count = 0;
    float acceptance_ratio = 0.0f;
    bool is_accepted = false;

    this->temperature = 0.0f;

    while(step_count < 20 || acceptance_ratio < 0.95f){
        while(!is_accepted){
            int i, j;
            std::tie(i, j) = get_random_pair(problem_instance->n);
            int delta = problem_instance->compute_cost_delta(current_solution, i, j, best_cost);
            if(this->accept_solution(delta, temperature)){
                accepted_count++;
                current_cost += delta;
                std::swap(current_solution[i], current_solution[j]);
                is_accepted = true;
            }else{
                rejected_count++;
                this->temperature += delta / 10.0f;
            }
        }
        if(current_cost < best_cost){
            best_cost = current_cost;
            std::copy(current_solution, current_solution + problem_instance->n, best_solution);
        }
        is_accepted = false;
        step_count++;
        index = (index + 1) % step_window;
        if(index >= step_window-1){
            acceptance_ratio = static_cast<float>(accepted_count) / (accepted_count + rejected_count);
            accepted_count = 0;
            rejected_count = 0;
        }
    }

    
}

bool SimulatedAnnealingSolver::accept_solution(int delta, float temperature)
{
    if(delta < 0){
        return true;
    }else{
        float acceptance_probability = std::exp(-delta / temperature);
        float random_value = get_random_number();
        if(random_value < acceptance_probability){
            return true;
        }
    }
    return false;
}

SimulatedAnnealingSolver::SimulatedAnnealingSolver() : GreedySearchSolver()
{
}

SimulatedAnnealingSolver::~SimulatedAnnealingSolver()
{
    GreedySearchSolver::~GreedySearchSolver();
}

void SimulatedAnnealingSolver::solve(int* const solution_ptr)
{
    int* best_solution = new int[this->problem_instance->n];
    this->problem_instance->get_random_solution(best_solution);
    int best_cost = this->problem_instance->compute_cost_quadratic(best_solution);
    this->adjust_initial_temperature(best_solution, best_cost);

    int* currentSolution = new int[this->problem_instance->n];
    this->problem_instance->get_random_solution(currentSolution);

    int current_cost = this->problem_instance->compute_cost_quadratic(currentSolution);
    int delta;
    bool step = true;
    bool improvement = true;
    int i, j;
    int steps_without_improvement = 0;
    const float initial_temperature = this->temperature;
    
    while(steps_without_improvement < this->max_no_improvement || this->temperature > 0.01f * initial_temperature){
        step = false;
        this->problem_instance->shuffle_neighborhood_2opt();
        while(!step){
            // iterate over the neighborhood until a solution is accepted or the neighborhood is exhausted
            for(auto neighborhood_it = this->problem_instance->get_neighborhood_iterator(); neighborhood_it != this->problem_instance->get_neighborhood_end(); neighborhood_it++){
                i = std::get<0>(*neighborhood_it);
                j = std::get<1>(*neighborhood_it);
                delta = this->problem_instance->compute_cost_delta(currentSolution, i, j, current_cost);
                step = this->accept_solution(delta, this->temperature);
                if(step){
                    this->problem_instance->apply_move_2opt(currentSolution, i, j);
                    current_cost += delta;
                    this->iterations_counter++;
                    break;
                }
                this->iterations_counter++;
            }
            steps_without_improvement++;
            // if new solution is better than the best solution, update the best solution
            if(current_cost < best_cost){
                best_cost = current_cost;
                std::copy(currentSolution, currentSolution + this->problem_instance->n, best_solution);
                steps_without_improvement = 0;
            }
        }
        // decrease the temperature
        if(this->iterations_counter % this->cooling_step == 0){
            this->temperature *= this->cooling_factor;
        }
    }

    std::copy(currentSolution, currentSolution + this->problem_instance->n, solution_ptr);
}

std::string SimulatedAnnealingSolver::get_name() const
{
    return "SimulatedAnnealingSolver";
}

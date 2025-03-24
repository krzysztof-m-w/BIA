#include "../include/json.hpp"
#include "../utils/time_measure.h"
#include "SolverEvaluator.h"
#include <fstream>

SolverEvaluator::SolverEvaluator(DataLoader* dl, std::vector<Solver*> solvers, std::vector<std::string> problem_names)
{
    this->dl = dl;
    this->solvers = solvers;
    for(auto problem_name : problem_names){
        this->dl->load_problem_instance(problem_name);
    }
}

SolverEvaluator::~SolverEvaluator()
{

}


void SolverEvaluator::save_results(
    const std::string& problem_name, 
    const std::string& solver_name,
    const std::list<int*>& solutions,
    const std::list<int>& iteration_counts,
    const std::list<int>& costs,
    const float avg_time,
    const int n
){
    // Create JSON object
    nlohmann::json jsonData;
    jsonData["problem_name"] = problem_name;
    jsonData["solver_name"] = solver_name;
    jsonData["avg_time"] = avg_time;
    auto it_solution = solutions.begin();
    auto it_iteration = iteration_counts.begin();
    auto it_cost = costs.begin();
    while (it_solution != solutions.end() && it_iteration != iteration_counts.end() && it_cost != costs.end()) {
        nlohmann::json solutionData;
        solutionData["solution"] = std::vector<int>(*it_solution, *it_solution + n);
        solutionData["iteration_counts"] = *it_iteration;
        solutionData["cost"] = *it_cost;
        jsonData["solutions"].push_back(solutionData);

        ++it_solution;
        ++it_iteration;
        ++it_cost;
    }

    // Save to file
    std::ofstream file("results/" + problem_name + "-" + solver_name + ".json");
    if (file.is_open()) {
        file << jsonData.dump(4); 
        file.close();
        std::cout << "JSON saved to data.json" << std::endl;
    } else {
        std::cerr << "Could not open file!" << std::endl;
    }
   
}

void SolverEvaluator::evaluate_solvers(){
    for(auto& pi : this->dl->problem_instances){
        for(auto solver : solvers){
            solver->set_problem_instance(&pi);
            int counter = 0;
            float avg_time;
            std::list<int*> solutions;
            std::list<int> iteration_counts;
            std::list<int> costs;
            TimePoint start_time = time_now();
            int* solution;
            do{
                // Memory must be freed at the end
                solution = new int[pi.n];

                // Ensure the solver starts from an initial configuration
                solver->reset();
                solver->solve(solution);

                solutions.push_back(solution);
                iteration_counts.push_back(solver->get_iterations_counter());
            }while (time_diff(start_time, time_now()) < 1 || counter++ < 100);
            TimePoint end_time = time_now();
            avg_time = time_diff(start_time, end_time) / counter;
            for(auto solution : solutions){
                costs.push_back(pi.compute_cost_quadratic(solution));
            }
            this->save_results(pi.name, solver->get_name(), solutions, iteration_counts, costs, avg_time, pi.n);
            // Free memory
            for(auto solution : solutions){
                delete[] solution;
            }

        }
    }
            
}

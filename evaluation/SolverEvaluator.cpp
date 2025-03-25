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
    const std::list<int>& step_counts,
    const float avg_time,
    const int n,
    const int optimal_cost
){
    // Create JSON object
    nlohmann::json jsonData;
    jsonData["problem_name"] = problem_name;
    jsonData["solver_name"] = solver_name;
    jsonData["avg_time"] = avg_time;
    jsonData["optimal_cost"] = optimal_cost;
    auto it_solution = solutions.begin();
    auto it_iteration = iteration_counts.begin();
    auto it_cost = costs.begin();
    auto it_step_counts = step_counts.begin();
    while (
        it_solution != solutions.end()
    ) {
        nlohmann::json solutionData;
        solutionData["solution"] = std::vector<int>(*it_solution, *it_solution + n);
        solutionData["iteration_counts"] = *it_iteration;
        solutionData["cost"] = *it_cost;
        solutionData["step_count"] = *it_step_counts;
        jsonData["solutions"].push_back(solutionData);

        ++it_solution;
        ++it_iteration;
        ++it_cost;
        ++it_step_counts;
    }

    // Save to file
    std::string file_name = "results/" + problem_name + "-" + solver_name + ".json";
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << jsonData.dump(4); 
        file.close();
        std::cout << "saving results to: " + file_name << std::endl;
    } else {
        std::cerr << "Could not open file!" << std::endl;
    }
   
}

void SolverEvaluator::evaluate_solvers(){
    for(auto& pi : this->dl->problem_instances){
        for(auto solver : solvers){
            solver->set_problem_instance(&pi);
            solver->read_configuration("", pi.name);
            int counter = 0;
            float avg_cost;
            float avg_time;
            std::list<int*> solutions;
            std::list<int> iteration_counts;
            std::list<int> costs;
            std::list<int> step_counts;
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
                step_counts.push_back(solver->get_step_counter());
                counter++;
            }while (time_diff(start_time, time_now()) < 1 || counter < 100);
            TimePoint end_time = time_now();
            avg_time = time_diff(start_time, end_time) / counter;
            for(auto solution : solutions){
                costs.push_back(pi.compute_cost_quadratic(solution));
            }
            this->save_results(
                pi.name,
                solver->get_name(),
                solutions,
                iteration_counts,
                costs,
                step_counts,
                avg_time,
                pi.n,
                pi.optimal_cost
            );
            // Free memory
            for(auto solution : solutions){
                delete[] solution;
            }

        }
    }
            
}

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
    const std::list<nlohmann::json>& solution_info,
    const float avg_time,
    const ProblemInstance* problem_instance
){
    // Create JSON object
    nlohmann::json jsonData;
    jsonData["problem_name"] = problem_name;
    jsonData["solver_name"] = solver_name;
    jsonData["avg_time"] = avg_time;
    jsonData["optimal_cost"] = problem_instance->optimal_cost;
    jsonData["optimal_solution"] = std::vector<int>(problem_instance->optimal_solution, problem_instance->optimal_solution + problem_instance->n);

    for(auto& solutionData: solution_info) {
        jsonData["solutions"].push_back(solutionData);
    }

    // Save to file
    std::string file_name = "results/" + problem_name + "-" + solver_name + ".json";
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << jsonData.dump(4); 
        file.close();
        std::cout << "saving results to: " + file_name << std::endl;
    } else {
        std::cerr << "Could not open file: " + file_name << std::endl;
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
            TimePoint start_time = time_now();
            int* solution;
            solution = new int[pi.n];
            do{
                // Memory must be freed at the end

                // Ensure the solver starts from an initial configuration
                solver->reset();
                solver->solve(solution);

                solver->set_solve_info(solution);
                counter++;
            }while (time_diff(start_time, time_now()) < 1 || counter < 100);
            TimePoint end_time = time_now();
            avg_time = time_diff(start_time, end_time) / counter;
            solver->add_cost_to_solve_info();
            delete[] solution;
            this->save_results(
                pi.name,
                solver->get_name(),
                solver->get_solution_info(),
                avg_time,
                &pi
            );
            // Free memory
        }
    }
            
}

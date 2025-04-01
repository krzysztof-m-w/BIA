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
            int total_counter = -1;
            float avg_cost;
            float avg_time;
            TimePoint start_time;
            int* solution;
            std::list<std::tuple<int, float>> avg_times;
            solution = new int[pi.n];
            for(int i=0; i<10; i++){
                start_time = time_now();
                do{
                    // Memory must be freed at the end

                    // Ensure the solver starts from an initial configuration
                    solver->reset();
                    solver->solve(solution);

                    solver->set_solve_info(solution);
                    counter++;
                }while (time_diff(start_time, time_now()) < 0.1);
                TimePoint end_time = time_now();
                avg_time = time_diff(start_time, end_time) / counter;
                avg_times.push_back(std::make_tuple(counter, avg_time));
                counter = 0;
            }
            solver->add_cost_to_solve_info();
            for(auto& time_result: avg_times){
                int current_counter = std::get<0>(time_result);
                float current_avg_time = std::get<1>(time_result);
                solver->add_time_to_solve_info(total_counter, current_counter, current_avg_time);
                total_counter += current_counter;
            }
            delete[] solution;
            this->save_results(
                pi.name,
                solver->get_name(),
                solver->get_solution_info(),
                avg_time,
                &pi
            );
        }
    }
            
}

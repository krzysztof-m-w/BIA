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


void SolverEvaluator::save_results(const std::string& file_name)
{
    // Create JSON object
    nlohmann::json jsonData;
    jsonData["name"] = "Alice";
    jsonData["age"] = 25;
    jsonData["scores"] = {95, 88, 76};

    // Save to file
    std::ofstream file("data.json");
    if (file.is_open()) {
        file << jsonData.dump(4); // Pretty print with 4 spaces
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
            TimePoint start_time = time_now();
            int counter = 0;
            std::vector<int*> solutions;
            do{
                int* solution = solver->solve();
                solutions.push_back(solution);
            }while (time_diff(start_time, time_now()) < 1 || counter++ < 100);


        }
    }
            
}

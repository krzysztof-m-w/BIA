#ifndef SOLVEREVALUATOR_H
#define SOLVEREVALUATOR_H

#include "../solvers/Solver.h"
#include "../utils/ProblemInstance.h"
#include "../utils/DataLoader.h"
#include "../include/json.hpp"

#include <list>

class SolverEvaluator
{
    private:
    void save_results(
        const std::string& problem_name, 
        const std::string& solver_name,
        const std::list<nlohmann::json>& solution_info,
        const float avg_time,
        const int n,
        const int optimal_cost
    );

        DataLoader* dl;
        std::vector<Solver*> solvers;
    public:
        SolverEvaluator(DataLoader* dl, std::vector<Solver*> solvers, std::vector<std::string> problem_names);
        ~SolverEvaluator();
        void evaluate_solvers();
};

#endif
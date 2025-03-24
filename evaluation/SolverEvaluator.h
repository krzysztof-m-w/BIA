#ifndef SOLVEREVALUATOR_H
#define SOLVEREVALUATOR_H

#include "../solvers/Solver.h"
#include "../utils/ProblemInstance.h"
#include "../utils/DataLoader.h"

class SolverEvaluator
{
    private:
    void save_results(
        const std::string& problem_name, 
        const std::string& solver_name,
        const std::vector<int*>& solutions,
        const std::vector<int>& iteration_counts,
        const std::vector<int>& costs,
        const float avg_time,
        const int n
    );

        DataLoader* dl;
        std::vector<Solver*> solvers;
    public:
        SolverEvaluator(DataLoader* dl, std::vector<Solver*> solvers, std::vector<std::string> problem_names);
        ~SolverEvaluator();
        void evaluate_solvers();
};

#endif
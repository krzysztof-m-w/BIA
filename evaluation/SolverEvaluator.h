#ifndef SOLVEREVALUATOR_H
#define SOLVEREVALUATOR_H

#include "../solvers/Solver.h"
#include "../utils/ProblemInstance.h"
#include "../utils/DataLoader.h"


class SolverEvaluator
{
    private:
        void save_results(const std::string& file_name);

        DataLoader* dl;
        std::vector<Solver*> solvers;
    public:
        SolverEvaluator(DataLoader* dl, std::vector<Solver*> solvers, std::vector<std::string> problem_names);
        ~SolverEvaluator();
        void evaluate_solvers();
};




#endif
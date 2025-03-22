#ifndef GREEDY_SEARCH_SOLVER_H
#define GREEDY_SEARCH_SOLVER_H

#include "Solver.h"

class GreedySearchSolver : public Solver {
    private:
        int* ininitialSolution;
    public:
        GreedySearchSolver();
        ~GreedySearchSolver();
        int* solve();
        void set_problem_instance(ProblemInstance* problem_instance);
};
        

#endif
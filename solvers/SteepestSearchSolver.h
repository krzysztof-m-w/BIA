#ifndef STEEPEST_SEARCH_SOLVER_H
#define STEEPEST_SEARCH_SOLVER_H

#include "Solver.h"

class SteepestSearchSolver : public Solver {
    private:
        int* ininitialSolution;
    public:
        SteepestSearchSolver();
        ~SteepestSearchSolver();
        int* solve();
        void set_problem_instance(ProblemInstance* problem_instance);
};
        

#endif